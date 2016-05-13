#include "events.C"
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TString.h> 

void FillHistograms(TString SAMPLE,bool isMC)
{
  cout<<"Processing sample "<<SAMPLE<<endl;
  TString PATH("");
  TFile *inf  = TFile::Open(PATH+"flatTree_"+SAMPLE+".root");
  TFile *outf = TFile::Open(TString::Format("Histo_%s.root",SAMPLE.Data()),"RECREATE");

  TH1F *hPass = (TH1F*)inf->Get("jetmet/TriggerPass");
  outf->mkdir("jetmet");  
  TDirectory *dir = (TDirectory*)outf->Get("jetmet"); 
  TTree *tr   = (TTree*)inf->Get("jetmet/events");
  events myTree(tr);
  dir->cd();
  hPass->Write("TriggerPass");
  myTree.Loop(dir,isMC);
  cout<<"Loop finished"<<endl;
  dir->Close();
  cout<<"directory closed"<<endl;
  delete tr;
  cout<<"Tree deleted"<<endl;
  outf->Close();
  inf->Close();
}
