package main

import "fmt"

func main() {
	// Find Score of an Array afeter Markinbg all elements
	array := []int{2, 1, 3, 4, 5, 2}

	fmt.Printf("result: %d", findScore(array)) // out: 212

}

func findScore(v []int) int64 {
	var r0 int64 = 0
	l := len(v)
	if l == 0 {
		return r0
	}

	lowest := findLowest(v)
	r0 += int64(v[lowest])
	upperBound := lowest + 2
	lowerBound := lowest - 1

	if lowerBound > 0 {
		r0 += findScore(v[:lowerBound])
	}

	if upperBound < l {
		r0 += findScore(v[upperBound:])
	}

	return r0
}

func findLowest(v []int) int {
	r := 0
	for i, n := range v {
		if n < v[r] {
			r = i
		}
	}
	return r
}
