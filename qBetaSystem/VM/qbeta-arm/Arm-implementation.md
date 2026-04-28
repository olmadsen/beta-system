This file is for adding documentation for the implementation of qBeta on a bare bone Arm-based Rasberry Pie. When the documentation is expanded, this file will be spilt into more pages with links between them.

## Attaching an object to a core

A class defining objects that may be attached to a core is a subclass of `SuperCore`:

````
SuperCore:
   %core 16
   main: ref SuperScheduler
   inner(SuperCore)
````
The class `Core` is defined in `BasicSystemLib.qbeta`:
````
Core: SuperCore
   %Public
   attach: 
      in M: ref Scheduler
      main := M
   %Private
   go: do
       loop: obj 
           if (main =/= none) :then 
              main.call 
           :else 
               sleep(100)
               restart(loop)
   (this(Core)).suspend
````
In the above code, class `Scheduler` is a subclass of class `SuperScheduler` – we plan to describe these classes elsewhere.

A `Scheduler` may be attached to a core in the following way:
````
C: obj Core         -- C is an instance of class Core
fork(C)             -- C is attached to a physical core 
C.attach(Scheduler) -- a Scheduler object is generated and
                    -- attached to C
````
The byte code `fork` implements the actual attachment of `C` to a physical core.

`Fork` calls the following run-time routine:
````
Bfork(interpreter,B,threadNo + 1);
````
where `interpreter` is the function implementing the VM, and `B` is a stuct defining various properties

`Bfork` is defined in the file `slib.S`.
