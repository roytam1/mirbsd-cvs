package main

import (
	"./simpleglob"
	"fmt"
	"os"
)


func main() {
	for _, a := range os.Args[1:] {
		matches := simpleglob.Glob(a)
		if matches == nil {
			fmt.Printf("Glob on %v not ok\n", a)
		} else {
			fmt.Printf("%v matches:\n", a)
			for _, m := range matches {
				fmt.Printf(" %v\n", m)
			}
		}
	}
}
