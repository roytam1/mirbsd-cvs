package main

import (
	"./glob"
	"fmt"
	"os"
)

func Err(filename string, err os.Error) bool {
	fmt.Printf("Err called for %v: %v\n", filename, err)
	return false
}

func main() {
	for _, a := range os.Args[1:] {
		matches, ok := glob.Glob(a, 0, Err)
		if !ok {
			fmt.Printf("Glob on %v not ok\n", a)
		} else {
			fmt.Printf("%v matches:\n", a)
			for _, m := range matches {
				fmt.Printf(" %v\n", m)
			}
		}
	}
}
