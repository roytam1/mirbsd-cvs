//	$MirOS: contrib/hosted/bsiegert/go-glob/glob.go,v 1.3 2010/09/26 11:37:55 bsiegert Exp $

package glob

import (
	"container/vector"
	"path"
	"os"
	"sort"
	"strings"
)

const (
	GLOB_ERR = 4 >> iota	// abort when a directory cannot be opened
	GLOB_MARK		// append a slash to matching pathnames
	GLOB_NOCHECK		// if no match, return the string unchanged
	GLOB_NOSORT		// do not sort the results alphabetically
	GLOB_BRACE		// expand {foo,bar} brace expansions
	GLOB_TILDE		// expand a '~' to the home directory
	GLOB_NOESCAPE = 0x2000
)

// expandTilde expands the tilde at the begining of path with the value
// of the $HOME environment variable. We cannot expand '~user' because
// getpwnam(3) is not available in Go.
func expandTilde(path string) string {
	if path[0] != '~' {
		return path
	}
	h := os.Getenv("HOME")
	if h == "" {
		return path
	}
	return h + path[1:]
}

func expandBraces(path string) []string {
	var (
		open, close int // index of the opening and the closing brace
		result, x vector.StringVector
	)

	open = strings.LastIndex(path, "{")
	close = strings.Index(path[open+1:], "}")
	if open == -1 || close == -1 {
		return []string{path}
	}
	substs := strings.Split(path[open+1:open+close-2], ",", -1)
	for _, s := range substs {
		exp := path[0:open] + s + path[open+close:]
		if strings.Index(exp, "{") != -1 {
			x = expandBraces(exp)
			result.AppendVector(&x)
		} else {
			result.Push(exp)
		}
	}
	return result
}
			

func GlobAll(patterns []string, flags int, errfunc func(string, os.Error) bool) ([]string, bool) {
	var (
		m, matches  vector.StringVector
		ok, sorting bool
	)
	matches = make([]string, 0)
	// For GlobAll, only sort the results at the end
	sorting = (flags&GLOB_NOSORT == 0)

	for _, p := range patterns {
		m, ok = Glob(p, flags|GLOB_NOSORT, errfunc)
		if !ok && flags&GLOB_ERR != 0 {
			if sorting {
				sort.Sort(&matches)
			}
			return matches, false
		}
		matches.AppendVector(&m)
	}
	if sorting {
		sort.Sort(&matches)
	}
	return matches, true
}


func Glob(pattern string, flags int, errfunc func(string, os.Error) bool) ([]string, bool) {
	if flags&GLOB_TILDE != 0 {
		pattern = expandTilde(pattern)
	}
	if !ContainsMagic(pattern) {
		if flags&GLOB_NOCHECK == 0 {
			if _, err := os.Stat(pattern); err != nil {
				ok := !errfunc(pattern, err)
				return []string{}, ok
			}
		}
		return []string{pattern}, true
	}
	dir, file := path.Split(pattern)
	if dir == "" {
		dir = "."
	}
	if ContainsMagic(dir) {
		dirs, ok := Glob(dir[0:len(dir)-1], flags, errfunc)
		if !ok {
			return []string{}, flags&GLOB_ERR == 0
		}
		newpatterns := make([]string, len(dirs))
		for i, d := range dirs {
			newpatterns[i] = path.Join(d, file)
		}
		return GlobAll(newpatterns, flags, errfunc)
	}

	return globInDir(dir[0:len(dir)-1], file, flags, errfunc)
}

// ContainsMagic returns true if path contains any of the magic characters
// recognized by path.Match.
func ContainsMagic(path string) bool {
	return strings.IndexAny(path, "*?[") != -1
}

func globInDir(dir, pattern string, flags int, errfunc func(string, os.Error) bool) ([]string, bool) {
	var matches vector.StringVector
	var didmatch bool

	print("globInDir ", dir, " ", pattern, "\n") //DEBUG

	_, err := os.Stat(dir)
	if err != nil {
		goto error
	}
	print("globInDir going to open ", dir, "\n") //DEBUG
	d, err := os.Open(dir, os.O_RDONLY, 0666)
	if err != nil {
		goto error
	}
	defer d.Close()

	print("globInDir going to readdirnames ", dir, "\n") //DEBUG
	names, err := d.Readdirnames(-1)
	if err != nil {
		goto error
	}

	for _, n := range names {
		didmatch, err = path.Match(pattern, n)
		if err != nil {
			goto error
		}
		if !didmatch {
			continue
		}
		fullname := path.Join(dir, n)
		if flags&GLOB_MARK > 0 {
			fi, err := os.Stat(fullname)
			if err != nil {
				goto error
			}
			if fi.IsDirectory() {
				fullname = fullname + "/"
			}
		}
		matches.Push(fullname)
	}

	if flags&GLOB_NOSORT == 0 {
		sort.Sort(&matches)
	}
	return matches, true

error:
	if errfunc != nil {
		return nil, !errfunc(dir, err)
	}
	return nil, flags&GLOB_ERR == 0
}
