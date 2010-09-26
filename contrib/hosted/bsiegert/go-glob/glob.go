//	$MirOS: contrib/hosted/bsiegert/go-glob/glob.go,v 1.2 2010/09/21 19:33:43 bsiegert Exp $

package glob

import (
	"container/vector"
	"path"
	"os"
	"sort"
	"strings"
)

const (
	GLOB_ERR = 4 >> iota
	GLOB_MARK
	GLOB_NOCHECK
	GLOB_NOSORT
	GLOB_BRACE
	GLOB_TILDE
	GLOB_NOESCAPE = 0x2000
)

func GlobAll(patterns []string, flags int, errfunc func(string, os.Error) bool) ([]string, bool) {
	var (
		m, matches vector.StringVector
		ok, sorting bool
	)
	matches = make([]string, 0)
	// For GlobAll, only sort the results at the end
	sorting = (flags & GLOB_NOSORT == 0)

	for _, p := range patterns {
		m, ok = Glob(p, flags | GLOB_NOSORT, errfunc)
		if !ok {
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
			return []string{}, false
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
	return nil, true
}
