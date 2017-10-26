#include "G4UIsession.hh"
#include "fstream"
#include "iostream"

#ifndef MimosaMySession_H
#define MimosaMySession_H 1

class MimosaMySession : public G4UIsession
{
    public:
        ofstream logFile, logFile1;
        G4int ReceiveG4cout(G4String coutString);
        G4int ReceiveG4cerr(G4String cerrString);
        
        MimosaMySession(){
            logFile.open("results", ios::app);
            logFile1.open("errors", ios::app);
        }
        
        ~MimosaMySession(){
            logFile.close();
            logFile1.close();
        }
};

G4int MimosaMySession::ReceiveG4cout(G4String coutString)
{
    logFile << coutString << flush;
    return 0;
}

G4int MimosaMySession::ReceiveG4cerr(G4String cerrString)
{
    logFile1 << cerrString << flush;
    return 0;
}
#endif
