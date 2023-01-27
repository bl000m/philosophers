# philosophers
Threads and philosophers. 42 School project.
This project is a training to multi-threads/multi-process programming with the use of mutex, in the form of a variant of the famous Dining Philosophers problem.

** If you are a 42 student visiting this page to get some inspiration please leave your inspiration being free not to copy/paste the code but catching logics behind that **

The specific rules for the mandatory part are:
```
• Each philosopher should be a thread.

• There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.

• To prevent philosophers from duplicating forks, you should protect the forks state
with a mutex for each of them.
