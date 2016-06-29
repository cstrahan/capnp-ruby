# little but powerful distributed computation system.
# made by Felipe Vieira, gsoc 2016 student

@0x9dfdcaa625365235;

struct Task {
  dataint @0 :Int32;
  madeBy @1 :Text;
}

interface Employer {
  put23 @0 ( taskSent :Task ) -> ( taskRecv :Task );
}

interface Master {
  wantToWork @0 ( ipOfWorker :Text ) -> ( hired :Bool);
}

interface Worker {
  work @0 (taskToProcess :Task) -> (taskProcessed :Task);
}
