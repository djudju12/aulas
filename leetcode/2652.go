package main

import "fmt"

func main() {
	fmt.Printf("expected: 21 / result: %d\n", sumOfMultiples(7))
	fmt.Printf("expected: 40 / result: %d\n", sumOfMultiples(10))
}

func sumOfMultiples(n int) int {
	// 3 5 7
	sum := 0
	for i := 1; i <= n; i++ {
		if i%3 == 0 {
			sum += i
		} else if i%5 == 0 {
			sum += i
		} else if i%7 == 0 {
			sum += i
		}
	}

	return sum
}
