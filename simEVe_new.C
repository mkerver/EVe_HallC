{
  /// Macro for running EVe with hodtest.root . Can easily be updated to work with any compatible .root file, or dynamically input as in simEVe.C    ///

  #include <TGClient.h>
  gSystem->Load("libGeom");
  gSystem->Load("libEVe.so");
  

  int nrun, nev;
  int found = 0;
  const char** path = 0;
  char filename[300];  
  FILE *fd;
  const char* paths[] = {  
    "/u/home/davispbr/hcana-copy/EVe/",
    "./",
    0
  };
  while( found==0 ) {
    //   cout << "Run number?\n";
    // cin >> nrun;
    //if( nrun<0 ) break;
   
    path=paths;
    
    while ( path && *path ) {
      sprintf(filename,"hodtest.root");
      fd = fopen(filename,"r");
      if (fd != NULL) {
	found = 1;
	cout << "Will analyze file "<<filename<<endl;
	break;
      }
      path++;
    }
    if ( (!path || !*path) && !found ) {
      cout << "File not found.  Try again, or -1 to quit.\n";
    }
  }
  //  if(nrun<0) return;
  cout << "Opening file "<<filename<<endl;


  EVe *sim = new EVe(gClient->GetRoot(),950,678);  
  sim->initRun(filename);
  
}
