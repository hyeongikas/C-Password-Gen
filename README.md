# CLI Password Generator

## Overview

This CLI Password Generator is a simple yet versatile tool written in C that allows users to generate random passwords based on their specified criteria. It provides flexibility in choosing password length and includes options for uppercase letters, lowercase letters, numbers, and special characters.

## Features

- **Customizable Password Criteria**: Users can specify the length of the password and choose whether to include uppercase letters, lowercase letters, numbers, and special characters.
  
- **Multiple Password Generation**: Generate multiple passwords in one go, with each password displayed along with its estimated strength.

- **Password Strength Estimation**: The tool estimates the strength of each generated password based on the variety of character types used (uppercase, lowercase, numbers, special characters).

- **Output to File**: Generated passwords can be saved to a `passwords.txt` file for easy access and management.

## Usage

### Requirements

- **C Compiler**: Ensure you have a C compiler installed on your system (e.g., GCC).
- **Libraries**: Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `math.h`) are used in this project.

### How to Use

1. **Compile the Program**:
   - Use your preferred C compiler to compile the `password_generator.c` file:
     ```bash
     gcc -o password_generator password_generator.c
     ```

2. **Run the Program**:
   - Execute the compiled binary:
     ```bash
     ./password_generator
     ```

3. **Follow the Prompts**:
   - The program will prompt you to enter the desired password length and specify whether to include uppercase letters, lowercase letters, numbers, and special characters.

4. **Generate Passwords**:
   - Enter the number of passwords you want to generate.
   - Each generated password and its estimated strength (Weak, Medium, or Strong) will be displayed in the terminal.
   - Passwords will also be saved to a `passwords.txt` file in the same directory.

## Example

Here’s a brief example of how to use the CLI Password Generator:

```plaintext
Enter password length (max 128): 12
Include uppercase letters? (y/n): y
Include lowercase letters? (y/n): y
Include numbers? (y/n): y
Include special characters? (y/n): y
How many passwords to generate? 5

Password 1: Ab5@Tc7#f@1 (Strong)
Password 2: Kp9$Qo8Uf#2 (Strong)
Password 3: 1mR3%lC5D@0b (Strong)
Password 4: 5zR$Tj2Dc@6& (Strong)
Password 5: Ht1#fJ9%oY+3 (Strong)
