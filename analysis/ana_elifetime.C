#define ana_elifetime_cxx
#include "ana_elifetime.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

const int kMaxEvent = 5000000;
const int kLoopEvent = 500; // per loop

void ana_elifetime::Loop()
{

  double diffphi = 0.3;
  double diffZ = 5;
  double crossDist = 20;

  size_t nbinsX = 15;
  double lowx = 0;
  double higx = 30;
  double divx = (higx - lowx)/nbinsX;

  size_t nbinsHPT= 20;
  double lowHPT = 0;
  double higHPT = 200;
  double divHPT = (higHPT - lowHPT)/nbinsHPT;


  double cutThetaXZ[4] = {30,80,100,150};
  double cutThetaYZ[6] = {52,60,85,95,122,130};
  double trk_len_cut = 10.;
  ////////////////////////


  // track length
  double lbin_trk_len = 0.;
  double hbin_trk_len = 160; // [cm]
  int nbin_trk_len = 160;
  
  // track angle
  double lbin_trk_thetaxz = -180.;
  double hbin_trk_thetaxz = 180.;
  int nbin_trk_thetaxz = 72.;

  double lbin_trk_thetayz = -180.;
  double hbin_trk_thetayz = 180.;
  int nbin_trk_thetayz = 72.;

  double radTodeg = 180.0/3.1415927;
  
  // hit
  int max_hits = 1000;



  // dqdx
  int nbin_dqdx = 100;
  double lbin_dqdx = 0.;
  double hbin_dqdx = 500.;

  int nbin_time = 250;
  double lbin_time = 0.;
  double hbin_time = 250.;

  int nbin_x = 200;
  double lbin_x = 0.;
  double hbin_x = 40.;


  // output
  TFile output("fout_ana_elifetime.root","recreate");


  TH1F *h1_trk_x_selected = new TH1F("h1_trk_x", "; x [cm]; Counts [#]", 40, 0., 40.);

  TH1F *h1_trk_x_len_selected = new TH1F("h1_trk_x_len_selected", "; Length in X [cm]; Counts [#]", 25, 25., 50);
  TH1F *h1_trk_y_len_selected = new TH1F("h1_trk_y_len_selected", "; Length in Y [cm]; Counts [#]", 25, 0., 50.);

  // Histograms
  TH1F *h1_trk_startx = new TH1F("h1_trk_startx", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_starty = new TH1F("h1_trk_starty", "; y [cm]; Counts [#]", 200, -10, 190.);
  TH1F *h1_trk_startz = new TH1F("h1_trk_startz", "; z [cm]; Counts [#]", 150, -10, 140);

  //No cuts
  TH2F *h2_trk_start_end_x = new TH2F("h2_trk_start_end_x", "; x Start [cm]; x End [cm]",120, -60., 60., 120, -60., 60.);
  TH2F *h2_trk_start_end_y = new TH2F("h2_trk_start_end_y", "; y Start [cm]; y End [cm]",200, -10., 190.,200, -10., 190.);
  TH2F *h2_trk_start_end_z = new TH2F("h2_trk_start_end_z", "; z Start [cm]; z End [cm]",150, -10,  140, 150, -10,  140);

  TH2F *h2_trk_startX_startY = new TH2F("h2_trk_startX_startY", "; x Start [cm]; y Start [cm]",120, -60., 60., 200, -10., 190.);
  TH2F *h2_trk_endX_endY = new TH2F("h2_trk_endX_endY", "; x End [cm]; y End [cm]",120, -60., 60., 200, -10., 190.);
  TH1F *h1_trk_y_len = new TH1F("h1_trk_y_len", "; Length in Y [cm]; Counts [#]", 25, 0., 50);  
  //Cuts
  TH1F *h1_trk_startx_selected = new TH1F("h1_trk_startx_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_starty_selected = new TH1F("h1_trk_starty_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_startz_selected = new TH1F("h1_trk_startz_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_startx_tpc0_selected = new TH1F("h1_trk_startx_tpc0_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_starty_tpc0_selected = new TH1F("h1_trk_starty_tpc0_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_startz_tpc0_selected = new TH1F("h1_trk_startz_tpc0_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_startx_tpc1_selected = new TH1F("h1_trk_startx_tpc1_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_starty_tpc1_selected = new TH1F("h1_trk_starty_tpc1_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_startz_tpc1_selected = new TH1F("h1_trk_startz_tpc1_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH2F *h2_trk_start_end_x_selected = new TH2F("h2_trk_start_end_x_selected", "; x Start [cm]; x End [cm]",120, -60., 60., 120, -60., 60.);
  TH2F *h2_trk_start_end_y_selected = new TH2F("h2_trk_start_end_y_selected", "; y Start [cm]; y End [cm]",200, -10., 190.,200, -10., 190.);
  TH2F *h2_trk_start_end_z_selected = new TH2F("h2_trk_start_end_z_selected", "; z Start [cm]; z End [cm]",150, -10,  140, 150, -10,  140);

  TH2F *h2_trk_startX_startY_selected = new TH2F("h2_trk_startX_startY_selected", "; x Start [cm]; y Start [cm]",120, -60., 60., 200, -10., 190.);
  TH2F *h2_trk_endX_endY_selected = new TH2F("h2_trk_endX_endY_selected", "; x End [cm]; y End [cm]",120, -60., 60., 200, -10., 190.);
  


  TH2F *h2_trk_start_end_x_tpc0_selected = new TH2F("h2_trk_start_end_x_tpc0_selected", "; x Start [cm]; x End [cm]",120, -60., 60., 120, -60., 60.);
  TH2F *h2_trk_start_end_y_tpc0_selected = new TH2F("h2_trk_start_end_y_tpc0_selected", "; y Start [cm]; y End [cm]",200, -10., 190.,200, -10., 190.);
  TH2F *h2_trk_start_end_z_tpc0_selected = new TH2F("h2_trk_start_end_z_tpc0_selected", "; z Start [cm]; z End [cm]",150, -10,  140, 150, -10,  140);

  TH2F *h2_trk_start_end_x_tpc1_selected = new TH2F("h2_trk_start_end_x_tpc1_selected", "; x Start [cm]; x End [cm]",120, -60., 60., 120, -60., 60.);
  TH2F *h2_trk_start_end_y_tpc1_selected = new TH2F("h2_trk_start_end_y_tpc1_selected", "; y Start [cm]; y End [cm]",200, -10., 190.,200, -10., 190.);
  TH2F *h2_trk_start_end_z_tpc1_selected = new TH2F("h2_trk_start_end_z_tpc1_selected", "; z Start [cm]; z End [cm]",150, -10,  140, 150, -10,  140);

  TH1F *h1_trk_endx = new TH1F("h1_trk_endx", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_endy = new TH1F("h1_trk_endy", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_endz = new TH1F("h1_trk_endz", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_endx_selected = new TH1F("h1_trk_endx_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_endy_selected = new TH1F("h1_trk_endy_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_endz_selected = new TH1F("h1_trk_endz_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_endx_tpc0_selected = new TH1F("h1_trk_endx_tpc0_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_endy_tpc0_selected = new TH1F("h1_trk_endy_tpc0_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_endz_tpc0_selected = new TH1F("h1_trk_endz_tpc0_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_endx_tpc1_selected = new TH1F("h1_trk_endx_tpc1_selected", "; x [cm]; Counts [#]", 120, -60., 60.);
  TH1F *h1_trk_endy_tpc1_selected = new TH1F("h1_trk_endy_tpc1_selected", "; y [cm]; Counts [#]", 200, -10, 190);
  TH1F *h1_trk_endz_tpc1_selected = new TH1F("h1_trk_endz_tpc1_selected", "; z [cm]; Counts [#]", 150, -10, 140);

  TH1F *h1_trk_len = new TH1F("h1_trk_len", "; Track length [cm]; Counts [#]", nbin_trk_len, lbin_trk_len, hbin_trk_len);
  TH1F *h1_trk_len_tpc0 = new TH1F("h1_trk_len_tpc0", "; Track length [cm]; Counts [#]", nbin_trk_len, lbin_trk_len, hbin_trk_len);
  TH1F *h1_trk_len_tpc1 = new TH1F("h1_trk_len_tpc1", "; Track length [cm]; Counts [#]", nbin_trk_len, lbin_trk_len, hbin_trk_len);
  
  TH1F *h1_trk_thetaxz = new TH1F("h1_trk_thetaxz", "; #theta_{xz} [deg]; Counts [#]", nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz);
  TH1F *h1_trk_thetayz = new TH1F("h1_trk_thetayz", "; #theta_{yz} [deg]; Counts [#]", nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);

  TH1F *h1_trk_thetaxz_with_cut = new TH1F("h1_trk_thetaxz_with_cut", "; #theta_{xz} [deg]; Counts [#]", nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz);
  TH1F *h1_trk_thetayz_with_cut = new TH1F("h1_trk_thetayz_with_cut", "; #theta_{yz} [deg]; Counts [#]", nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);


  TH2F *h2_trk_angle = new TH2F("h2_trk_angle", "; #theta_{xz}[deg]; #theta_{yz}[deg]", nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz, nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);
  TH2F *h2_trk_angle_with_cut = new TH2F("h2_trk_angle_with_cut", "; #theta_{xz}[deg]; #theta_{yz}[deg]", nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz, nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);

  TH2F *h2_dqdxhitpeakt_allplanes = new TH2F("h2_dqdxhitpeakt_allplanes", "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, 0., higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
  TH2F *h2_dqdxhitpeakt_allplanes_trunc = new TH2F("h2_dqdxhitpeakt_allplanes_trunc", "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, 0., higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
  TH2F *h2_dqdxhitpeakt_allplanes_selected = new TH2F("h2_dqdxhitpeakt_allplanes_selected", "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, 0., higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
  TH2F *h2_dqdxhitpeakt_tpc0_allplanes_selected = new TH2F("h2_dqdxhitpeakt_tpc0_allplanes_selected", "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, 0., higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
  TH2F *h2_dqdxhitpeakt_tpc1_allplanes_selected = new TH2F("h2_dqdxhitpeakt_tpc1_allplanes_selected", "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, 0., higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);

  TProfile2D *hp2d_angle[3];

  TH1F* h1_dqdx[3];
  TH2F* h2_dqdxtime[3];
  TH2F* h2_dqdxhitpeakt[3];
  TH2F* h2_dqdxhitpeakt_tpc0[3];
  TH2F* h2_dqdxhitpeakt_tpc1[3];
  TH2F* h2_dqdxhitpeakt_tpc0_trunc[3];
  TH2F* h2_dqdxhitpeakt_tpc1_trunc[3];
  TH2F* h2_dqdxX[3];
  TH2F* h2_dqdxX_tpc0[3];
  TH2F* h2_dqdxX_tpc1[3];
  TProfile2D *hp2d_angle_dqdx[3];



  for (int p=0; p<3; p++) {

    hp2d_angle[p] = new TProfile2D(TString::Format("hp2d_angle_plane_%d",p), TString::Format("Plane %d; #theta_{xz} [deg]; #theta_{yz} [deg]", p), nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz, nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);

    h1_dqdx[p] = new TH1F(TString::Format("h1_dqdx_plane_%d",p), "; dQ/dx [ADC/cm]; Counts [#]", nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxtime[p] = new TH2F(TString::Format("h2_dqdxtime_plane_%d",p), "; Drift time [#mus]; dQ/dx [ADC/cm]", nbin_time, lbin_time, hbin_time, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxhitpeakt[p] = new TH2F(TString::Format("h2_dqdxhitpeakt_plane_%d",p), "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, lowHPT, higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxhitpeakt_tpc0[p] = new TH2F(TString::Format("h2_dqdxhitpeakt_tpc0_plane_%d",p), "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, lowHPT, higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxhitpeakt_tpc1[p] = new TH2F(TString::Format("h2_dqdxhitpeakt_tpc1_plane_%d",p), "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, lowHPT, higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxhitpeakt_tpc0_trunc[p] = new TH2F(TString::Format("h2_dqdxhitpeakt_tpc0_plane_%d_trunc",p), "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, lowHPT, higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxhitpeakt_tpc1_trunc[p] = new TH2F(TString::Format("h2_dqdxhitpeakt_tpc1_plane_%d_trunc",p), "; Hit Peak Time [#mus]; dQ/dx [ADC/cm]", 100, lowHPT, higHPT, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxX[p] = new TH2F(TString::Format("h2_dqdxX_plane_%d",p), "; Drift Distance [cm]; dQ/dx [ADC/cm]", nbin_x, lbin_x, hbin_x, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxX_tpc0[p] = new TH2F(TString::Format("h2_dqdxX_tpc0_plane_%d",p), "; Drift Distance [cm]; dQ/dx [ADC/cm]", nbin_x, lbin_x, hbin_x, nbin_dqdx, lbin_dqdx, hbin_dqdx);
    h2_dqdxX_tpc1[p] = new TH2F(TString::Format("h2_dqdxX_tpc1_plane_%d",p), "; Drift Distance [cm]; dQ/dx [ADC/cm]", nbin_x, lbin_x, hbin_x, nbin_dqdx, lbin_dqdx, hbin_dqdx);

    hp2d_angle_dqdx[p] = new TProfile2D(TString::Format("hp2d_angle_dqdx_plane_%d",p), TString::Format("Plane %d; #theta_{xz} [deg]; #theta_{yz} [deg]", p), nbin_trk_thetaxz, lbin_trk_thetaxz, hbin_trk_thetaxz, nbin_trk_thetayz, lbin_trk_thetayz, hbin_trk_thetayz);
  }
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout << "nentries: " << nentries << endl;

   int maxplots = (int) nentries/kLoopEvent + 1;
   int runs[maxplots];
   TH1F *h1_ntrks_loop = new TH1F("h1_ntrks_loop","h1_ntrks_loop",maxplots,0,maxplots);
   TH1F* h1_dqdxVSddist_tpc0[maxplots][3];
   TH1F* h1_dqdxVSddist_tpc1[maxplots][3];

   TH1F* h1_dqdxVShpeaktime_tpc0[maxplots][3];
   TH1F* h1_dqdxVShpeaktime_tpc1[maxplots][3];
   TH1F* h1_dqdxVShpeaktime[maxplots][3];


   for (int n = 0; n < maxplots; ++n){
     for (int p=0; p<3; p++) {
        h1_dqdxVSddist_tpc0[n][p] = new TH1F(TString::Format("h1_dqdxVSddist_tpc0_n_%d_plane_%d",n,p), "; X [cm]; Median dQ/dx [ADC/cm]", nbinsX, lowx, higx);
        h1_dqdxVSddist_tpc1[n][p] = new TH1F(TString::Format("h1_dqdxVSddist_tpc1_n_%d_plane_%d",n,p), "; X [cm]; Median dQ/dx [ADC/cm]", nbinsX, lowx, higx);
        h1_dqdxVShpeaktime_tpc0[n][p] = new TH1F(TString::Format("h1_dqdxVSpeaktime_tpc0_n_%d_plane_%d",n,p), "; Hit Peak Time [#mus]; Median dQ/dx [ADC/cm]", nbinsHPT, lowHPT, higHPT);
        h1_dqdxVShpeaktime_tpc1[n][p] = new TH1F(TString::Format("h1_dqdxVSpeaktime_tpc1_n_%d_plane_%d",n,p), "; Hit Peak Time [#mus]; Median dQ/dx [ADC/cm]", nbinsHPT, lowHPT, higHPT);
        h1_dqdxVShpeaktime[n][p] = new TH1F(TString::Format("h1_dqdxVSpeaktime_n_%d_plane_%d",n,p), "; Hit Peak Time [#mus]; Median dQ/dx [ADC/cm]", nbinsHPT, lowHPT, higHPT);

     }
     runs[n] = 0;
   }

   std::vector<int> ntrks0_v, ntrks1_v;
   Long64_t nbytes = 0, nb = 0;
   size_t eventNum = 0;

   vector < double > dqdx_tpc0_v[nbinsX][3];
   vector < double > dqdx_tpc1_v[nbinsX][3];
   vector < double > dqdx_tpc0_hpt_v[nbinsHPT][3];
   vector < double > dqdx_tpc1_hpt_v[nbinsHPT][3];
   vector < double > dqdx_hpt_v[nbinsHPT][3];

   int nplot = 0; int trkCounter0 = 0; int trkCounter1 = 0; int trkCounter = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {//event level
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if(ntrks == 0) continue;//consider only events with tracks

      double med0 = 0., error0 = 0.;
      double med1 = 0., error1 = 0.;
      double med01 = 0., error01 = 0.;
      if(eventNum%kLoopEvent == 0 && eventNum != 0){
        //cout<< "Filling " << TString::Format("h1_dqdxVSddist_n_%d_plane_X",nplot) << endl;
        for (int ip = 0; ip < 3; ++ip){
          for (int ix = 0; ix < nbinsX; ++ix){
            med0 = Median(dqdx_tpc0_v[ix][ip]);
            med1 = Median(dqdx_tpc1_v[ix][ip]);
            error0 = sqrt(dqdx_tpc0_v[ix][ip].size());
            error1 = sqrt(dqdx_tpc1_v[ix][ip].size());
            h1_dqdxVSddist_tpc0[nplot][ip]->SetBinContent(ix, med0);
            h1_dqdxVSddist_tpc0[nplot][ip]->SetBinError(ix, error0);
            h1_dqdxVSddist_tpc1[nplot][ip]->SetBinContent(ix, med1);
            h1_dqdxVSddist_tpc1[nplot][ip]->SetBinError(ix, error1);

          }
          for(int ihpt = 0; ihpt < nbinsHPT; ihpt++){
            med0 = Median(dqdx_tpc0_hpt_v[ihpt][ip]);
            med1 = Median(dqdx_tpc1_hpt_v[ihpt][ip]);
            med1 = Median(dqdx_tpc1_hpt_v[ihpt][ip]);
            error0 = sqrt(dqdx_tpc0_hpt_v[ihpt][ip].size());
            error1 = sqrt(dqdx_tpc1_hpt_v[ihpt][ip].size());
            med01 = Median(dqdx_hpt_v[ihpt][ip]);
            error01 = sqrt(dqdx_hpt_v[ihpt][ip].size());
            h1_dqdxVShpeaktime_tpc0[nplot][ip]->SetBinContent(ihpt, med0);
            h1_dqdxVShpeaktime_tpc0[nplot][ip]->SetBinError(ihpt, error0);
            h1_dqdxVShpeaktime[nplot][ip]->SetBinContent(ihpt, med01);
            h1_dqdxVShpeaktime[nplot][ip]->SetBinError(ihpt, error01);
            h1_dqdxVShpeaktime_tpc1[nplot][ip]->SetBinContent(ihpt, med1);
            h1_dqdxVShpeaktime_tpc1[nplot][ip]->SetBinError(ihpt, error1);

          }
        }
        runs[nplot] = run;
        h1_ntrks_loop->SetBinContent(nplot,trkCounter);


        for (int ip = 0; ip < 3; ++ip){
          for (int ix = 0; ix < nbinsX; ++ix){
            dqdx_tpc0_v[ix][ip].clear();
            dqdx_tpc1_v[ix][ip].clear();
          }
          for(int ihpt = 0; ihpt < nbinsHPT; ihpt++){
            dqdx_tpc0_hpt_v[ihpt][ip].clear();
            dqdx_tpc1_hpt_v[ihpt][ip].clear();
            dqdx_hpt_v[ihpt][ip].clear();
          }
        }
        nplot++;
        trkCounter = 0;
        ntrks0_v.push_back(trkCounter0); ntrks1_v.push_back(trkCounter1);
        trkCounter0 = 0; trkCounter1 = 0;
      }
      
      std::vector<int> trk_index_selected_tpc0;
      std::vector<int> trk_index_selected_tpc1;
      for (int i=0; i<ntrks; i++) {
        h1_trk_startx->Fill(trkstart[i][0]);
        h1_trk_starty->Fill(trkstart[i][1]);
        h1_trk_startz->Fill(trkstart[i][2]);

        h1_trk_endx->Fill(trkend[i][0]);
        h1_trk_endy->Fill(trkend[i][1]);
        h1_trk_endz->Fill(trkend[i][2]);

        // record track angle
        double thetaxz_deg = trkthetaxz[i]*radTodeg;
        double thetayz_deg = trkthetayz[i]*radTodeg;
        h1_trk_thetaxz->Fill(thetaxz_deg);
        h1_trk_thetayz->Fill(thetayz_deg);
        h2_trk_angle->Fill(trkthetaxz[i]*radTodeg, trkthetayz[i]*radTodeg);

        h2_trk_start_end_y->Fill(trkstart[i][1],trkend[i][1]);
        h2_trk_start_end_x->Fill(trkstart[i][0],trkend[i][0]);
        h2_trk_start_end_z->Fill(trkstart[i][2],trkend[i][2]);

        h2_trk_startX_startY->Fill(trkstart[i][0],trkstart[i][1]);
        h2_trk_endX_endY->Fill(trkend[i][0],trkend[i][1]);
        if(trklen[i] > trk_len_cut) h1_trk_y_len->Fill(abs(trkstart[i][1] - trkend[i][1]));


        //trkthetaxz and trkthetayz are recorded as from 0 to +-180 depending on the quadrant of vector. 
        thetaxz_deg = abs(thetaxz_deg); thetayz_deg = abs(thetayz_deg);
  
        //cutThetaXZ[4] = {30,80,100,150};
        if(thetaxz_deg < cutThetaXZ[0] || (thetaxz_deg > cutThetaXZ[1] && thetaxz_deg < cutThetaXZ[2]) || thetaxz_deg > cutThetaXZ[3]) continue;
        //cutThetaYZ[6] = {52,60,85,95,122,130};
        if((thetayz_deg > cutThetaYZ[0] && thetayz_deg < cutThetaYZ[1]) || (thetayz_deg > cutThetaYZ[2] && thetayz_deg < cutThetaYZ[3]) || 
            (thetayz_deg > cutThetaYZ[4] && thetayz_deg < cutThetaYZ[5])) continue;
        if(trklen[i] < trk_len_cut) continue; // remove very short tracks
        double trklenX = abs(trkstart[i][0] - trkend[i][0]);
        if(trklenX < 28) continue;
        if(trkstart[i][1] < 75 || trkstart[i][1] > 175) continue;
        if(trkend[i][1] < 75 || trkend[i][1] > 175) continue;
        if(trkstart[i][0] > -5 && trkend[i][0] > 0){
          trk_index_selected_tpc1.push_back(i);
        }else if(trkstart[i][0] < 5 && trkend[i][0] < 0){
          trk_index_selected_tpc0.push_back(i);
        }
        for (int ip=0; ip<3; ip++) {// trkdqdx[ntrks][planes][hits];
          for (int jj=0; jj<max_hits; jj++) {//looping hits
            h2_dqdxhitpeakt_allplanes->Fill(trkhitpeakt[i][ip][jj], trkdqdx[i][ip][jj]);
          }
        }
      }
      if(trk_index_selected_tpc0.size() > 0 || trk_index_selected_tpc1.size() > 0) trkCounter += trk_index_selected_tpc1.size() + trk_index_selected_tpc0.size();
      if(trk_index_selected_tpc0.size() > 0 ) trkCounter0 += trk_index_selected_tpc0.size();
      if(trk_index_selected_tpc1.size() > 0 ) trkCounter1 += trk_index_selected_tpc1.size();
      for (int i=0; i<ntrks; i++) {// looping through tracks
        int intpc;
        if (std::find(trk_index_selected_tpc0.begin(), trk_index_selected_tpc0.end(), i) != trk_index_selected_tpc0.end()){
          intpc = 0;
        }else if(std::find(trk_index_selected_tpc1.begin(), trk_index_selected_tpc1.end(), i) != trk_index_selected_tpc1.end()){
          intpc = 1;
        }else{
          continue;
        }

      	h1_trk_startx_selected->Fill(trkstart[i][0]);
      	h1_trk_starty_selected->Fill(trkstart[i][1]);
      	h1_trk_startz_selected->Fill(trkstart[i][2]);

      	h1_trk_endx_selected->Fill(trkend[i][0]);
      	h1_trk_endy_selected->Fill(trkend[i][1]);
      	h1_trk_endz_selected->Fill(trkend[i][2]);

      	h1_trk_len->Fill(trklen[i]);

        h2_trk_start_end_y_selected->Fill(trkstart[i][1],trkend[i][1]);
        h2_trk_start_end_x_selected->Fill(trkstart[i][0],trkend[i][0]);
        h2_trk_start_end_z_selected->Fill(trkstart[i][2],trkend[i][2]);

        h2_trk_startX_startY_selected->Fill(trkstart[i][0],trkstart[i][1]);
        h2_trk_endX_endY_selected->Fill(trkend[i][0],trkend[i][1]);


        h1_trk_x_len_selected->Fill(abs(trkstart[i][0] - trkend[i][0]));
        h1_trk_y_len_selected->Fill(abs(trkstart[i][1] - trkend[i][1]));
      
        if(intpc == 0){
          h1_trk_startx_tpc0_selected->Fill(trkstart[i][0]);
          h1_trk_starty_tpc0_selected->Fill(trkstart[i][1]);
          h1_trk_startz_tpc0_selected->Fill(trkstart[i][2]);
  
          h1_trk_endx_tpc0_selected->Fill(trkend[i][0]);
          h1_trk_endy_tpc0_selected->Fill(trkend[i][1]);
          h1_trk_endz_tpc0_selected->Fill(trkend[i][2]);
  
          h1_trk_len_tpc0->Fill(trklen[i]);
          h2_trk_start_end_x_tpc0_selected->Fill(trkstart[i][0],trkend[i][0]);
          h2_trk_start_end_y_tpc0_selected->Fill(trkstart[i][1],trkend[i][1]);
          h2_trk_start_end_z_tpc0_selected->Fill(trkstart[i][2],trkend[i][2]);
        }
        if(intpc == 1){
          h1_trk_startx_tpc1_selected->Fill(trkstart[i][0]);
          h1_trk_starty_tpc1_selected->Fill(trkstart[i][1]);
          h1_trk_startz_tpc1_selected->Fill(trkstart[i][2]);
  
          h1_trk_endx_tpc1_selected->Fill(trkend[i][0]);
          h1_trk_endy_tpc1_selected->Fill(trkend[i][1]);
          h1_trk_endz_tpc1_selected->Fill(trkend[i][2]);
  
          h1_trk_len_tpc1->Fill(trklen[i]);
          h2_trk_start_end_x_tpc1_selected->Fill(trkstart[i][0],trkend[i][0]);
          h2_trk_start_end_y_tpc1_selected->Fill(trkstart[i][1],trkend[i][1]);
          h2_trk_start_end_z_tpc1_selected->Fill(trkstart[i][2],trkend[i][2]);
        }
      	// track angle
      	double thetaxz_deg = trkthetaxz[i]*radTodeg;
      	double thetayz_deg = trkthetayz[i]*radTodeg;
      	h1_trk_thetaxz_with_cut->Fill(thetaxz_deg);
      	h1_trk_thetayz_with_cut->Fill(thetayz_deg);
      
      	h2_trk_angle_with_cut->Fill(trkthetaxz[i]*radTodeg, trkthetayz[i]*radTodeg);

  	    for (int ip=0; ip<3; ip++) {// trkdqdx[ntrks][planes][hits];
          //std::vector< pair<float, float> > hpt_dqdx_0_v, hpt_dqdx_1_v;
          std::vector< pair<float, float> > hpt_dqdx_v;
	        for (int jj=0; jj<max_hits; jj++) {//looping hits
	          if (trkdqdx[i][ip][jj] == -9999.0 || trkx[i][ip][jj] == -9999.0 || trkt[i][ip][jj] == -9999.0) continue;
            pair<float, float> temp_hpt_dqdx;
	          h1_dqdx[ip]->Fill(trkdqdx[i][ip][jj]);
	          h2_dqdxtime[ip]->Fill(trkt[i][ip][jj], trkdqdx[i][ip][jj]);
            h2_dqdxhitpeakt[ip]->Fill(trkhitpeakt[i][ip][jj], trkdqdx[i][ip][jj]);
            
            h2_dqdxX[ip]->Fill(trkx[i][ip][jj], trkdqdx[i][ip][jj]);

            h2_dqdxhitpeakt_allplanes_selected->Fill(trkhitpeakt[i][ip][jj], trkdqdx[i][ip][jj]);

            temp_hpt_dqdx.second = trkhitpeakt[i][ip][jj]; temp_hpt_dqdx.first = trkdqdx[i][ip][jj];
            hpt_dqdx_v.push_back(temp_hpt_dqdx);
            if(intpc == 1) {
              h2_dqdxX_tpc1[ip]->Fill(trkx[i][ip][jj], trkdqdx[i][ip][jj]);
              h2_dqdxhitpeakt_tpc1[ip]->Fill(trkhitpeakt[i][ip][jj], trkdqdx[i][ip][jj]);
              //hpt_dqdx_1_v.push_back(temp_hpt_dqdx);
            }
            if(intpc == 0) {
              h2_dqdxX_tpc0[ip]->Fill(trkx[i][ip][jj], trkdqdx[i][ip][jj]);
              h2_dqdxhitpeakt_tpc0[ip]->Fill(trkhitpeakt[i][ip][jj], trkdqdx[i][ip][jj]);
              //hpt_dqdx_0_v.push_back(temp_hpt_dqdx);
            }
	          
            hp2d_angle_dqdx[ip]->Fill(thetaxz_deg, thetayz_deg, trkdqdx[i][ip][jj]);
            h1_trk_x_selected->Fill(trkx[i][ip][jj]);
            for(int xb = 0; xb < nbinsX; xb++){
              double lowerX = lowx + divx*xb; double upperX = lowerX + divx;
              if(trkx[i][ip][jj] > lowerX && trkx[i][ip][jj] < upperX){
                if(intpc == 0) dqdx_tpc0_v[xb][ip].push_back(trkdqdx[i][ip][jj]); 
                if(intpc == 1) dqdx_tpc1_v[xb][ip].push_back(trkdqdx[i][ip][jj]); 
                break;
              }
            }
            for(int ihpt = 0; ihpt < nbinsHPT; ihpt++){
              double lowerHPT = lowHPT + divHPT*ihpt; double upperHPT = lowerHPT + divHPT;
              if(trkhitpeakt[i][ip][jj] > lowerHPT && trkhitpeakt[i][ip][jj] < upperHPT){
                if(intpc == 0) dqdx_tpc0_hpt_v[ihpt][ip].push_back(trkdqdx[i][ip][jj]); 
                if(intpc == 1) dqdx_tpc1_hpt_v[ihpt][ip].push_back(trkdqdx[i][ip][jj]);
                dqdx_hpt_v[ihpt][ip].push_back(trkdqdx[i][ip][jj]); 
                break;
              }
            }
	        }
          //cout << "hpt_dqdx_v.size() = " << hpt_dqdx_v.size() << endl;
          if (hpt_dqdx_v.size() < 10) continue;
          hpt_dqdx_v = Truncate(hpt_dqdx_v);

          for (size_t jj = 0; jj < hpt_dqdx_v.size(); ++jj){
            if(intpc == 0) h2_dqdxhitpeakt_tpc0_trunc[ip]->Fill(hpt_dqdx_v[jj].second, hpt_dqdx_v[jj].first);
            if(intpc == 1) h2_dqdxhitpeakt_tpc1_trunc[ip]->Fill(hpt_dqdx_v[jj].second, hpt_dqdx_v[jj].first);
            h2_dqdxhitpeakt_allplanes_trunc->Fill(hpt_dqdx_v[jj].second, hpt_dqdx_v[jj].first);
          }
          hpt_dqdx_v.clear();
  	    }//loop over ip
        


      }
      runs[nplot] = run;
      if(eventNum > kMaxEvent) break;
      eventNum++;
      // if (Cut(ientry) < 0) continue;
   }
   h1_ntrks_loop->SetBinContent(nplot,trkCounter);
   for (int ip = 0; ip < 3; ++ip){
      for (int ix = 0; ix < nbinsX; ++ix){
        h1_dqdxVSddist_tpc0[nplot][ip]->SetBinContent(ix, Median(dqdx_tpc0_v[ix][ip]));
        h1_dqdxVSddist_tpc1[nplot][ip]->SetBinContent(ix, Median(dqdx_tpc1_v[ix][ip]));
        h1_dqdxVSddist_tpc0[nplot][ip]->SetBinError(ix, sqrt(dqdx_tpc0_v[ix][ip].size()));
        h1_dqdxVSddist_tpc1[nplot][ip]->SetBinError(ix, sqrt(dqdx_tpc1_v[ix][ip].size())); 
      }
      for(int ihpt = 0; ihpt < nbinsHPT; ihpt++){
        h1_dqdxVShpeaktime_tpc0[nplot][ip]->SetBinContent(ihpt,Median(dqdx_tpc0_hpt_v[ihpt][ip]));
        h1_dqdxVShpeaktime_tpc1[nplot][ip]->SetBinContent(ihpt,Median(dqdx_tpc1_hpt_v[ihpt][ip]));
        h1_dqdxVShpeaktime_tpc0[nplot][ip]->SetBinError(ihpt,sqrt(dqdx_tpc0_hpt_v[ihpt][ip].size()));
        h1_dqdxVShpeaktime_tpc1[nplot][ip]->SetBinError(ihpt,sqrt(dqdx_tpc1_hpt_v[ihpt][ip].size()));
        h1_dqdxVShpeaktime[nplot][ip]->SetBinContent(ihpt,Median(dqdx_hpt_v[ihpt][ip]));
        h1_dqdxVShpeaktime[nplot][ip]->SetBinError(ihpt,sqrt(dqdx_hpt_v[ihpt][ip].size()));
      }
   }
   ntrks0_v.push_back(trkCounter0); ntrks1_v.push_back(trkCounter1);

   int numLoops = ntrks0_v.size();
   TH1F *h1_ntrks_loop_0 = new TH1F("h1_ntrks_loop_tpc0", "; Loop; ntrks", numLoops, 0, numLoops);
   TH1F *h1_ntrks_loop_1 = new TH1F("h1_ntrks_loop_tpc1", "; Loop; ntrks", numLoops, 0, numLoops);

   for (size_t loop = 0; loop < numLoops; ++loop){
     h1_ntrks_loop_0->SetBinContent(loop,ntrks0_v[loop]);
     h1_ntrks_loop_1->SetBinContent(loop,ntrks1_v[loop]);
   }

  //double vd = 0.156461; // cm/us
  double m0 = 0, tau0 = 0;
  std::vector<pair < int, double> > run_elife_tpc0_plane2_v;
  for (size_t plot = 0; plot < maxplots; ++plot){
    for (int ip = 0; ip < 3; ++ip){
      pair < int, double > run_elife;
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime_tpc0[plot][ip])) continue;
      if(h1_dqdxVShpeaktime_tpc0[plot][ip]->GetEntries() == 0) continue;
      h1_dqdxVShpeaktime_tpc0[plot][ip]->Fit("expo","Q0","",10,180);
      
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime_tpc0[plot][ip]->GetListOfFunctions()->FindObject("expo");
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m0 = (exp->GetParameter(1));
        tau0 = -(1/m0);
        cout << "TPC0: Electron Liftime is: " << tau0 << " us on plane: " << ip << ", for run: " << runs[plot] << endl;
        run_elife.first = runs[plot]; run_elife.second = tau0;
      }else{
        run_elife.first = runs[plot]; run_elife.second = -1;
      }
      if(ip == 2) run_elife_tpc0_plane2_v.push_back(run_elife);
    }
  }
  //TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
  int nplots0 = run_elife_tpc0_plane2_v.size();
  Double_t runr0[nplots0], life0[nplots0];
  //TH1F *h1_run_elife_tpc0_plane2 = new TH1F("h1_run_elife_plane2", "; Run Number; Electron Lifetime [#mus]", nplots, run_elife_tpc1_plane2_v[0].first, run_elife_tpc1_plane2_v[nplots - 1].first);
  for (int i = 0; i < nplots0; ++i){
    runr0[i] = run_elife_tpc0_plane2_v[i].first;
    life0[i] = run_elife_tpc0_plane2_v[i].second;
  }
  TGraph* g1_eLifeVSRun_tpc0_plane2 = new TGraph(nplots0,runr0,life0);
  g1_eLifeVSRun_tpc0_plane2->SetName("g1_eLifeVSRun_tpc0_plane2");
  g1_eLifeVSRun_tpc0_plane2->SetTitle("Run 3 Electron Lifetime - Plane 2, TPC 0");
  g1_eLifeVSRun_tpc0_plane2->GetXaxis()->SetTitle("Run Number");
  g1_eLifeVSRun_tpc0_plane2->GetYaxis()->SetTitle("Electron Lifetime [#mus]");
  //gr->Draw("A*");

  g1_eLifeVSRun_tpc0_plane2->Write();

  cout << endl;
  double m1 = 0, tau1 = 0;
  std::vector<pair < int, double> > run_elife_tpc1_plane2_v;
  for (size_t plot = 0; plot < maxplots; ++plot){
    for (int ip = 0; ip < 3; ++ip){
      pair < int, double > run_elife;
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime_tpc1[plot][ip])) continue;
      if(h1_dqdxVShpeaktime_tpc1[plot][ip]->GetEntries() == 0) continue;
      h1_dqdxVShpeaktime_tpc1[plot][ip]->Fit("expo","Q0","",10,180);
      
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime_tpc1[plot][ip]->GetListOfFunctions()->FindObject("expo");
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m1 = (exp->GetParameter(1));
        tau1 = -(1/m1);
        cout << "TPC1: Electron Liftime is: " << tau1 << " us on plane: " << ip << ", for run: " << runs[plot] << endl;
        run_elife.first = runs[plot]; run_elife.second = tau1;
      }else{
        run_elife.first = runs[plot]; run_elife.second = -1;
      }
      if(ip == 2) run_elife_tpc1_plane2_v.push_back(run_elife);
    }
  }
  //TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
  int nplots1 = run_elife_tpc1_plane2_v.size();
  Double_t runr1[nplots1], life1[nplots1];
  //TH1F *h1_run_elife_plane2 = new TH1F("h1_run_elife_plane2", "; Run Number; Electron Lifetime [#mus]", nplots, run_elife_tpc1_plane2_v[0].first, run_elife_tpc1_plane2_v[nplots - 1].first);
  for (int i = 0; i < nplots1; ++i){
    runr1[i] = run_elife_tpc1_plane2_v[i].first;
    life1[i] = run_elife_tpc1_plane2_v[i].second;
    //h1_run_elife_plane2->SetBinContent(run_elife_tpc1_plane2_v[i].first,run_elife_tpc1_plane2_v[i].second);
  }
  TGraph* g1_eLifeVSRun_tpc1_plane2 = new TGraph(nplots1,runr1,life1);
  g1_eLifeVSRun_tpc1_plane2->SetName("g1_eLifeVSRun_tpc1_plane2");
  g1_eLifeVSRun_tpc1_plane2->SetTitle("Run 3 Electron Lifetime - Plane 2, TPC 1");
  g1_eLifeVSRun_tpc1_plane2->GetXaxis()->SetTitle("Run Number");
  g1_eLifeVSRun_tpc1_plane2->GetYaxis()->SetTitle("Electron Lifetime [#mus]");
  //gr->Draw("A*");

  g1_eLifeVSRun_tpc1_plane2->Write();




  double m01 = 0, tau01 = 0;
  std::vector<pair < int, double> > run_elife_tpc01_plane2_v;
  std::vector<double> error01_v;
  for (size_t plot = 0; plot < maxplots; ++plot){
    for (int ip = 0; ip < 3; ++ip){
      pair < int, double > run_elife;
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime[plot][ip])) continue;
      if(h1_dqdxVShpeaktime[plot][ip]->GetEntries() == 0) continue;
      h1_dqdxVShpeaktime[plot][ip]->Fit("expo","Q0","",10,180);
      
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime[plot][ip]->GetListOfFunctions()->FindObject("expo");
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m01 = (exp->GetParameter(1));
        error01_v.push_back(exp->GetParError(1));
        tau01 = -(1/m01);
        cout << "TPC01: Electron Liftime is: " << tau01 << " us on plane: " << ip << ", for run: " << runs[plot] << endl;
        run_elife.first = runs[plot]; run_elife.second = tau01;
      }else{
        run_elife.first = runs[plot]; run_elife.second = -1;
      }
      if(ip == 2) run_elife_tpc01_plane2_v.push_back(run_elife);
    }
  }
  //TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
  int nplots01 = run_elife_tpc01_plane2_v.size();
  Double_t runr01[nplots01], life01[nplots01], error_elife01[nplots01], zeros[nplots01];
  //TH1F *h1_run_elife_tpc0_plane2 = new TH1F("h1_run_elife_plane2", "; Run Number; Electron Lifetime [#mus]", nplots, run_elife_tpc1_plane2_v[0].first, run_elife_tpc1_plane2_v[nplots - 1].first);
  for (int i = 0; i < nplots01; ++i){
    runr01[i] = run_elife_tpc01_plane2_v[i].first;
    life01[i] = run_elife_tpc01_plane2_v[i].second;
    error_elife01[i] = pow(run_elife_tpc01_plane2_v[i].second, 2)*error01_v[i];
    zeros[i] = 0;
  }
  TGraphErrors* g1_eLifeVSRun_tpc01_plane2 = new TGraphErrors(nplots01,runr01,life01,zeros,error_elife01);
  g1_eLifeVSRun_tpc01_plane2->SetName("g1_eLifeVSRun_tpc01_plane2");
  g1_eLifeVSRun_tpc01_plane2->SetTitle("Run 3 Electron Lifetime - Plane 2");
  g1_eLifeVSRun_tpc01_plane2->GetXaxis()->SetTitle("Run Number");
  g1_eLifeVSRun_tpc01_plane2->GetYaxis()->SetTitle("Electron Lifetime [#mus]");
  //gr->Draw("A*");

  g1_eLifeVSRun_tpc01_plane2->Write();


  output.Write();
  output.Close();

  cout << "C'est la fin" << endl;

}




