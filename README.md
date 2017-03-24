# get_next_line @ 42
This project is the final starting project before branching out. The goal is to
make a function which reads a single line from a file descriptor, assuming it
isn't being tampered with in between calls to the function.
It must fit in one source file and one header.

## Usage
```c
char *line;

// To get a single line
get_next_line(fd, &line);
...
ft_strdel(&line); // You should free after you're done using your line

// To read a whole file
while (get_next_line(fd, &line))
{
	// process the line here, here we'll just output it
	ft_putstr(line);
	
	// free the line to avoid leaking memory
	ft_strdel(&line);
}

// GNL will automatically free appropriately whenever it reaches EOF.
```
