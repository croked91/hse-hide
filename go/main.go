package main

import (
	"fmt"
	"os"
	"path/filepath"
)

const darkDirectory = "./.dark_directory"

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Path to file not found. Usage: hide <filename>")
		return
	}

	fileName := os.Args[1]

	if _, err := os.Stat(fileName); os.IsNotExist(err) {
		fmt.Printf("File %s does not exist.\n", fileName)
		return
	}

	if err := os.MkdirAll(darkDirectory, 0755); err != nil {
		fmt.Printf("Failed to create dark directory: %s\n", err)
		return
	}

	newFilePath := filepath.Join(darkDirectory, fileName)

	if err := os.Rename(fileName, newFilePath); err != nil {
		fmt.Printf("Failed to move file: %s\n", err)
		return
	}

	if err := os.Chmod(darkDirectory, 0111); err != nil {
		fmt.Printf("Failed to set permissions for dark directory: %s\n", err)
		return
	}

	fmt.Printf("File %s has been hidden in %s\n", fileName, newFilePath)
}
