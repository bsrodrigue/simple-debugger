#include "libsdb/process.hpp"
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <memory>


std::unique_ptr<sdb::process> sdb::process::launch(std::filesystem::path path) {
   pid_t pid;

   if ((pid = fork()) < 0) {
      perror("Fork failed");
      std::exit(-1);
   }

   // Child process
   if (pid == 0) {
      if (ptrace(PTRACE_TRACEME, 0, nullptr, nullptr) < 0) {
         perror("Tracing failed");
         std::exit(-1);
      }

      // Replace fork with target program
      if (execlp(path.c_str(), path.c_str(), nullptr) < 0) {
         // Exec failed
         perror("Execution failed");
         std::exit(-1);
      }
   }

   std::unique_ptr<process> proc (new process(pid, /*terminate_on_end=*/true));
   proc->wait_on_signal();

   return proc;
}


std::unique_ptr<sdb::process> sdb::process::attach(pid_t pid) {
   if (pid == 0) {
      // Invalid PID
   }

   if (ptrace(PTRACE_ATTACH, pid, nullptr, nullptr) < 0) {
      perror("Could not attach");
      std::exit(-1);
   }

   std::unique_ptr<process> proc(new process(pid, /*terminate_on_end=*/false));
   proc->wait_on_signal();

   return proc;
}
