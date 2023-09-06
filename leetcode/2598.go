package main

import (
	"fmt"
	"os"
)

func main() {
	vetor := []int{0, 0, 0, 5, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1}
	value := 3
	candidates := make([]int, len(vetor))
	for i := 0; i < len(vetor); i++ {
		candidates[(vetor[i]%value+value)%value] = candidates[(vetor[i]%value+value)%value] + 1
		fmt.Printf("%v\n", candidates)
	}
	fmt.Print("\n")

	for i := 0; i < len(vetor); i++ {
		if candidates[i%value] == 0 {
			fmt.Printf("%d\n", i)
		}
		candidates[i%value] = candidates[i%value] - 1
		fmt.Printf("%v\n", candidates)

	}
	fmt.Printf("%d", len(vetor))

	// check([]int{0, 2, 1, 5, 4, 3}, 5, 6)
	// check([]int{3, 0, 3, 2, 4, 2, 1, 1, 0, 4}, 5, 10)
	// check([]int{1, -10, 7, 13, 6, 8}, 5, 4)
	// check([]int{1, -10, 7, 13, 6, 8}, 7, 2)
	// check([]int{0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1}, 2, 15)
}

func check(arr []int, value int, expected int) {
	result := findSmallestInteger(arr, value)
	fmt.Printf("\narr: %v / Value: %d\nResult: %d <=> Expected: %d\n------\n", arr, value, result, expected)
	if result != expected {
		os.Exit(1)
	}
}

// func findSmallestInteger(nums []int, value int) int {

func findSmallestInteger(nums []int, value int) int {
	currentMin := 0

	i := 0
	for {
		if i == len(nums) {
			break
		}

		if (nums[i]-currentMin)%value == 0 {
			nums[i] = nums[currentMin]
			nums[currentMin] = currentMin
			currentMin++
			i = currentMin
		} else {
			i++
		}

	}
	return currentMin
}
