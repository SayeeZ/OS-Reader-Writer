# Reader-Writer Problem Solution using Semaphores, Mutex, and Pthreads

This repository contains a solution to the classical Reader-Writer problem implemented in C language, utilizing semaphores, mutex, and pthreads.

## Problem Description

The Reader-Writer problem involves multiple threads that consist of:
- **Readers:** Concurrently read a shared resource.
- **Writers:** Concurrently write to the shared resource.

The constraints are as follows:
- Multiple readers can access the resource simultaneously.
- Only one writer can modify the resource, and no other thread (reader or writer) can access it while writing is in progress.

## Solution Implementation

### Files Included
- rw_s.c : This file contains solution of classical reader-writer problem using semaphore & pthreads.
- rw_m.c : This file contains solution of classical reader-writer problem using mutex & pthreads.

### Solution Components
- **Semaphores:** Used to control access to the shared resource.
- **Mutex (Mutual Exclusion Lock):** Ensures exclusive access to the resource for writers.
- **Pthreads:** POSIX threads library utilized to create and manage threads.

## How to Use

1. Clone the repository:

    
    git clone https://github.com/your-username/reader-writer-solution.git
   

2. Compile the code:

   Compile the code in linux environment (one like WSL) if you don't have one use online compiler.  



    


