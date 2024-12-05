package main

import (
	"fmt"
	"hellogoroutine/threadinfo"
	"sync"
)

func printHello(wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Println("Hello, world!")
}

func main() {
	var wg sync.WaitGroup
	for i := 0; i < 4; i++ {
		wg.Add(1)
		go printHello(&wg)
	}
	wg.Wait()

	threadinfo.Threadinfo()
}
