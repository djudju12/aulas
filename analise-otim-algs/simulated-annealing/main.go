package main

import (
	"fmt"
	"log"
	"os"
	"simulated-annealing/sa"
	"strconv"
	"strings"
)

var testsPassed = 0

func main() {
	basePathIn := "inputs/low-dimensional"
	basePathOut := "inputs/low-dimensional-optimum"
	// basePathIn := "inputs/large_scale"
	// basePathOut := "inputs/large_scale-optimum"
	dirEntries, err := os.ReadDir(basePathIn)
	if err != nil {
		panic(err)
	}
	for _, dir := range dirEntries {
		filePathInput := basePathIn + "/" + dir.Name()
		filePathTest := basePathOut + "/" + dir.Name()
		testContent := readFileStr(filePathTest)
		expectedResult, err := strconv.ParseFloat(testContent, 64)
		if err != nil {
			log.Fatalf("error parsing. File: %s err: %s", filePathTest, err)
		}

		content := readFileStr(filePathInput)
		problemData := strings.Fields(content)
		solver := sa.NewSolver(problemData)

		initialSolution := solver.GenerateNaiveSolution()
		finalSolution := solver.Solve(300, 0.99, 2000, initialSolution)
		testResult(
			solver.TotalValue(initialSolution),
			expectedResult,
			solver.TotalValue(finalSolution),
			dir.Name(),
		)
	}

	fmt.Printf("total passed tests = %d\n", testsPassed)
}

func testResult(initial, expected, actual float64, testName string) {
	if expected != actual {
		fmt.Print("[X] ")
	} else {
		testsPassed++
		fmt.Print("[V] ")
	}

	fmt.Printf("%s\t| EXPECT: %10.2f | ACTUAL: %10.2f | INITIAL: %10.2f\n", testName, expected, actual, initial)
}

func readFileStr(filepath string) string {
	data, err := os.ReadFile(filepath)
	if err != nil {
		panic(err)
	}

	return string(data)
}
