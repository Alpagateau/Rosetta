# What is rosetta 
Rosetta is a runtime that compiles or interpret code from markdown files. 
For example, you can run this python code right here :
```python 
#1
#no number
print("Hello world")
```
by typing :
```bash 
rosetta README.md python
```

## How does it work ?
It reads your mardown file, and builds a temporary file, joining your code blocks. After that, it uses thedefined command to run or compile the code. It then removes the file. 
