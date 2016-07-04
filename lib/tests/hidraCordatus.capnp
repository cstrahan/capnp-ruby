# made by Felipe Vieira, gsoc 2016 student

@0x9dfdcaa625365235;

struct Task {
  dataint @0 :Int32;
  madeBy @1 :Text;
}

interface Employer {
  getWorker @0 () -> ( worker :Worker );
}

interface Worker {
  put23 @0 (taskToProcess :Task) -> (taskProcessed :Task);
}
