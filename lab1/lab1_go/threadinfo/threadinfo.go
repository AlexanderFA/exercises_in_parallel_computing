package threadinfo

import (
	"fmt"
	"sync"
)

func printThreadInfo(threadNum int, totalThreads int, wg *sync.WaitGroup) {
	defer wg.Done()
	fmt.Printf("I am %d thread from %d threads!\n", threadNum, totalThreads)
}

func Threadinfo() {
	var k int
	fmt.Println("Enter the number of threads:")
	fmt.Scan(&k)

	var wg sync.WaitGroup

	for i := 0; i < k; i++ {
		wg.Add(1)
		go printThreadInfo(i+1, k, &wg)
	}

	wg.Wait()
}
