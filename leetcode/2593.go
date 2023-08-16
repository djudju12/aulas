package main

import "fmt"

func main() {
	// Find Score of an Array afeter Markinbg all elements
	array := []int{2, 1, 3, 4, 5, 2}
	score := findScore(array)
	fmt.Printf("result: %d", score) // out: 212

}

func findScore(v []int) int64 {
	var score int64
	findScoreImpl(v, &score)
	return score
}

func findScoreImpl(v []int, r *int64) {
	l := len(v)
	if l == 0 {
		// return 0
		return
	}

	// var r0 int64 = 0
	lowest := findLowest(v)
	// r0 += int64(v[lowest])
	*r += int64(v[lowest])

	upperBound := lowest + 2
	lowerBound := lowest - 1

	if lowerBound > 0 {
		// r0 += findScore(v[:lowerBound])
		findScoreImpl(v[:lowerBound], r)
	}

	if upperBound < l {
		// r0 += findScore(v[upperBound:])
		findScoreImpl(v[upperBound:], r)
	}
}

func findLowest(v []int) int {
	r := 0
	for i := 1; i < len(v); i++ {
		if v[i] < v[r] {
			r = i
		}
	}
	return r
}
