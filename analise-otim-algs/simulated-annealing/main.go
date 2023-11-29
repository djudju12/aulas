package main

import (
	"fmt"
	"log"
	"os"
	"simulated-annealing/sa"
	"strconv"
	"strings"
)

func main() {
	basePathIn := "inputs/low-dimensional"
	basePathOut := "inputs/low-dimensional-optimum"
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
		finalSolution := solver.Solve(4000, 0.98, 2000, initialSolution)
		testResult(expectedResult, solver.TotalValue(finalSolution), dir.Name())

	}

}

func testResult(expected, actual float64, testName string) {
	if expected != actual {
		fmt.Print("[X] ")
	} else {
		fmt.Print("[V] ")
	}
	fmt.Printf("%s\t|\tEXPECT: %6.2f\t|\tACTUAL: %6.2f\n", testName, expected, actual)
}

func readFileStr(filepath string) string {
	data, err := os.ReadFile(filepath)
	if err != nil {
		panic(err)
	}

	return string(data)
}
