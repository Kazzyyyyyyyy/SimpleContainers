# SimpleContainers
Diy STL containers, I made as a learning project to get a deeper understanding of containers and how/when to use them.

# What I've learned 
 - difference between static and non static arrays
 - classes and structs (knew that before from C#, but its the first time that I used it in C++)
 - operator[] 
 - which container is good and performant in which situation and why
 - working with pointers and new/delete
 - how different containers operate
 - what are and how to use templates 
 - basics on how to test code properly
 - the basics of performance oriented thinking

## Implemented Containers
 - Vector
 - Stack (LinkedList and Array) 
 - Queue 
 - PriorityQueue 
 - HashSet 
 - HashMap

# State of the project 
All containers work and there are no obvious bugs. I tested all containers with self written tests and fixed all bugs I found. 
Queue, Vector and HashSet were already tested in the project im working on right now and they all worked well.
The code is pretty clean, commented and reusable, even though I would recommend just using the STL containers for projects.

## Note 
Not all containers are fully "templated". HashSet and HashMap are locked to struct(int, int) for the key. That is, because a hash function that fully supports templates and all datatypes that come with it,
is not so easy to do. So I just made it, how I need the containers for my new project.