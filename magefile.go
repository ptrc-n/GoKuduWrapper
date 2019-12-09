// +build mage

package main

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
)

// Default target to run when none is specified
// If not set, running mage will list available targets
// var Default = Build

func checkDockerDaemonRunning() error {
	out, err := exec.Command("sudo", "docker", "image", "ls").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	return nil
}

// PrepareKuduImage for later use as a basis for GoKuduWrapperTestImage (will take >1h)
func PrepareKuduImage() error {
	err := checkDockerDaemonRunning()
	if err != nil {
		return err
	}
	// Check Kudu Image existing
	out, err := exec.Command("sudo", "docker", "inspect", "--type=image", "apache/kudu:latest-xenial").CombinedOutput()
	if err == nil {
		return errors.New("Kudu Image does already exist, nothing to be done!")
	}
	// Clone Kudu Repo
	out, err = exec.Command("git", "clone", "https://github.com/apache/kudu.git").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	// Build Kudu Image
	exec.Command("cd", "kudu").CombinedOutput()
	cmd := exec.Command("sudo", "/usr/bin/bash", "docker/docker-build.sh")
	cmd.Env = append(
		os.Environ(),
		"BASES=ubuntu:xenial",
		"TARGETS=build,kudu",
	)
	cmd.Dir = "./kudu"
	out, err = cmd.CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	fmt.Println("Success: PrepareKuduImage complete!")
	return nil
}

// BuildTestImage prepares an image to be run for an exhaustive wrapper-check
func BuildTestImage() error {
	err := checkDockerDaemonRunning()
	if err != nil {
		return err
	}
	// Check Test Image existing
	out, err := exec.Command("sudo", "docker", "inspect", "--type=image", "ptrc-n/go-kudu-wrapper:test").CombinedOutput()
	if err == nil {
		return errors.New("Image does already exist, use ForceBuildTestImage if thats what you want")
	}
	// Check Kudu Image existing
	out, err = exec.Command("sudo", "docker", "inspect", "--type=image", "apache/kudu:latest-xenial").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	// Build Wrapper Test Image
	out, err = exec.Command("sudo", "docker", "build", "--tag=ptrc-n/go-kudu-wrapper:test", "-f", "container/Dockerfile", ".").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	fmt.Println("Success: BuildTestImage complete!")
	return nil
}

// ForceBuildTestImage will build the testing Image even if it already exists
func ForceBuildTestImage() error {
	err := checkDockerDaemonRunning()
	if err != nil {
		return err
	}
	// Check Kudu Image existing
	out, err := exec.Command("sudo", "docker", "inspect", "--type=image", "apache/kudu:latest-xenial").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	// Build Wrapper Test Image
	out, err = exec.Command("sudo", "docker", "build", "--tag=ptrc-n/go-kudu-wrapper:test", "-f", "container/Dockerfile", ".").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	fmt.Println("Success: BuildTestImage complete!")
	return nil
}

// RunTestImage will carry out all wrapper-checks
func RunTestImage() error {
	err := checkDockerDaemonRunning()
	if err != nil {
		return err
	}
	// Check Test Image existing
	out, err := exec.Command("sudo", "docker", "inspect", "--type=image", "ptrc-n/go-kudu-wrapper:test").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	out, err = exec.Command("sudo", "docker", "run", "-it", "ptrc-n/go-kudu-wrapper:test", "tests").CombinedOutput()
	if err != nil {
		return errors.New(string(out))
	}
	fmt.Println("Success: All tests run successfully!")
	return nil
}
