//	$MirOS: contrib/hosted/bsiegert/go-glob/simpleglob.go,v 1.1 2010/10/11 18:29:15 bsiegert Exp $

package simpleglob

import (
	"container/vector"
	"path"
	"os"
	"strings"
)

// Glob returns the names of all files matching pattern or nil
// if there is no matching file. The syntax used by pattern is like in
// path.Match. The pattern can contain a pathname.
func Glob(pattern string) []string {
	var m, matches vector.StringVector

	if !ContainsMagic(pattern) {
		if _, err := os.Stat(pattern); err == nil {
			return []string{pattern}
		}
		return nil
	}
		
	dir, file := path.Split(pattern)
	switch dir {
	case "":
		dir = "."
	case "/":
		// nothing
	default:
		dir = dir[0:len(dir)-1] // chop off tailing '/'
	}

	if ContainsMagic(dir) {
		for _, d := range Glob(dir) {
			m = Glob(path.Join(d, file))
			matches.AppendVector(&m)
		}
	} else {
		print("globInDir ", dir, " ", file, "\n") //DEBUG

		fi, err := os.Stat(dir)
		if err != nil || !fi.IsDirectory() {
			return nil
		}
		print("globInDir going to open ", dir, "\n") //DEBUG
		d, err := os.Open(dir, os.O_RDONLY, 0666)
		if err != nil {
			return nil
		}
		defer d.Close()

		print("globInDir going to readdirnames ", dir, "\n") //DEBUG
		names, err := d.Readdirnames(-1)
		if err != nil {
			return nil
		}

		for _, n := range names {
			didmatch, err := path.Match(file, n)
			if err != nil {
				return nil
			}
			if didmatch {
				matches.Push(path.Join(dir, n))
			}
		}
	}
	return matches
}

// ContainsMagic returns true if path contains any of the magic characters
// recognized by path.Match.
func ContainsMagic(path string) bool {
	return strings.IndexAny(path, "*?[") != -1
}
