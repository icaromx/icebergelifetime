//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug 18 09:32:23 2020 by ROOT version 6.18/04
// from TTree Event/Event
// found on file: eLifetime.root
//////////////////////////////////////////////////////////

#ifndef ana_elifetime_h
#define ana_elifetime_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class ana_elifetime {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   
   // Declaration of leaf types
   Int_t           event;
   Int_t           run;
   Int_t           subrun;
   Double_t        evttime;
   Int_t           year_month_date;
   Int_t           hour_min_sec;
   Int_t           ntrks;
   Int_t           trkid[627];   //[ntrks]
   Float_t         trkstart[627][3];   //[ntrks]
   Float_t         trkend[627][3];   //[ntrks]
   Float_t         trklen[627];   //[ntrks]
   Float_t         trkphi[627];   //[ntrks]
   Float_t         trktheta[627];   //[ntrks]
   Float_t         trkthetaxz[627];   //[ntrks]
   Float_t         trkthetayz[627];   //[ntrks]
   Float_t         trkstartcosxyz[627][3];   //[ntrks]
   Float_t         trkendcosxyz[627][3];   //[ntrks]
   Int_t           ntrkhits[627][3];   //[ntrks]
   Float_t         trkdqdx[627][3][1000];   //[ntrks]
   Float_t         trkhitpeakt[627][3][1000];   //[ntrks]
   Float_t         trkx[627][3][1000];   //[ntrks]
   Float_t         trkt[627][3][1000];   //[ntrks]
   //Double_t        trkhitx[627][3][1000];   //[ntrks]
   //Double_t        trkhity[627][3][1000];   //[ntrks]
   //Double_t        trkhitz[627][3][1000];   //[ntrks]
   Double_t        nplane[627][3][1000];   //[ntrks]

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_evttime;   //!
   TBranch        *b_year_month_date;   //!
   TBranch        *b_hour_min_sec;   //!
   TBranch        *b_ntrks;   //!
   TBranch        *b_trkid;   //!
   TBranch        *b_trkstart;   //!
   TBranch        *b_trkend;   //!
   TBranch        *b_trklen;   //!
   TBranch        *b_trkphi;   //!
   TBranch        *b_trktheta;   //!
   TBranch        *b_trkthetaxz;   //!
   TBranch        *b_trkthetayz;   //!
   TBranch        *b_trkstartcosxyz;   //!
   TBranch        *b_trkendcosxyz;   //!
   TBranch        *b_ntrkhits;   //!
   TBranch        *b_trkdqdx;   //!
   TBranch        *b_trkhitpeakt;   //!
   TBranch        *b_trkx;   //!
   TBranch        *b_trkt;   //!
   //TBranch        *b_trkhitx;   //!
   //TBranch        *b_trkhity;   //!
   //TBranch        *b_trkhitz;   //!
   TBranch        *b_nplane;   //!

   ana_elifetime(/*TTree *tree=0,*/ TString filename);
   virtual ~ana_elifetime();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual double   Median(vector< double > );
   virtual std::vector< pair<float, float> > Truncate(std::vector< pair<float, float> >);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef ana_elifetime_cxx
ana_elifetime::ana_elifetime( TString filename) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree *tree=0;
   
   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Form("%s.root",filename.Data()));
   if (!f || !f->IsOpen()) {
      f = new TFile(Form("%s.root",filename.Data()));
   }
   TDirectory * dir = (TDirectory*)f->Get(Form("%s.root:/icebergelifetime",filename.Data()));
   cout << "dir = " << dir << endl;
   cout << Form("%s.root:icebergelifetime",filename.Data()) << endl;
   dir->GetObject("Event",tree);

   Init(tree);
   Loop();
}

ana_elifetime::~ana_elifetime()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ana_elifetime::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ana_elifetime::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ana_elifetime::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_subrun);
   fChain->SetBranchAddress("evttime", &evttime, &b_evttime);
   fChain->SetBranchAddress("year_month_date", &year_month_date, &b_year_month_date);
   fChain->SetBranchAddress("hour_min_sec", &hour_min_sec, &b_hour_min_sec);
   fChain->SetBranchAddress("ntrks", &ntrks, &b_ntrks);
   fChain->SetBranchAddress("trkid", trkid, &b_trkid);
   fChain->SetBranchAddress("trkstart", trkstart, &b_trkstart);
   fChain->SetBranchAddress("trkend", trkend, &b_trkend);
   fChain->SetBranchAddress("trklen", trklen, &b_trklen);
   fChain->SetBranchAddress("trkphi", trkphi, &b_trkphi);
   fChain->SetBranchAddress("trktheta", trktheta, &b_trktheta);
   fChain->SetBranchAddress("trkthetaxz", trkthetaxz, &b_trkthetaxz);
   fChain->SetBranchAddress("trkthetayz", trkthetayz, &b_trkthetayz);
   fChain->SetBranchAddress("trkstartcosxyz", trkstartcosxyz, &b_trkstartcosxyz);
   fChain->SetBranchAddress("trkendcosxyz", trkendcosxyz, &b_trkendcosxyz);
   fChain->SetBranchAddress("ntrkhits", ntrkhits, &b_ntrkhits);
   fChain->SetBranchAddress("trkdqdx", trkdqdx, &b_trkdqdx);
   fChain->SetBranchAddress("trkhitpeakt", trkhitpeakt, &b_trkhitpeakt);
   fChain->SetBranchAddress("trkx", trkx, &b_trkx);
   fChain->SetBranchAddress("trkt", trkt, &b_trkt);
   //fChain->SetBranchAddress("trkhitx", trkhitx, &b_trkhitx);
   //fChain->SetBranchAddress("trkhity", trkhity, &b_trkhity);
   //fChain->SetBranchAddress("trkhitz", trkhitz, &b_trkhitz);
   fChain->SetBranchAddress("nplane", nplane, &b_nplane);
   Notify();
}

Bool_t ana_elifetime::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana_elifetime::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana_elifetime::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

double ana_elifetime::Median(vector<double> vec){
  size_t vsize = vec.size();
  double median = 0.;
  if (vsize == 0){
     return median;
  }
  
  sort(vec.begin(), vec.end()); 
  if (vsize%2 == 0){
    median = (vec[vsize / 2 - 1] + vec[vsize / 2])/2.;
  }else if(vsize%2 != 0){
    median = vec[vsize / 2];
  }else{
    median = 0.;
  }
  return median;
}



std::vector< pair<float, float> > ana_elifetime::Truncate(std::vector< pair<float, float> > vect){
    //bool sortbysec(const pair<float,float> &a, const pair<int,int> &b) { return (a.second < b.second); }
   

   size_t vectSize = vect.size();
   float redvectsizeby = (float) vectSize*0.25;
   
   size_t newvectsize = vectSize - (size_t)redvectsizeby;
   size_t startat = (size_t) (redvectsizeby/2.);
   
   std::vector< pair<float, float> > result_v;
   sort(vect.begin(), vect.end());
   for (size_t i = startat; i < newvectsize; ++i){
      result_v.push_back(vect[i]);
   }
   return result_v;
}

#endif // #ifdef ana_elifetime_cxx
