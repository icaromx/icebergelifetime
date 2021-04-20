TString getDir( const std::string& subdir ){
         TString getdir( subdir );
         if( 0 != system( Form( "test -d %s", getdir.Data()))){
                 std::cout << subdir << " directory does not exist, making one now.... " << std::endl;
     int madedir = system( Form( "mkdir -m 755 -p %s", getdir.Data() ) );
     if( 0 != madedir ) std::cout << "HistoDir, Could not make plot directory, " << getdir << std::endl;
    }
  return getdir;
}

void plot(TString FILENAME, TString RUNNUM) {
  int nplots = 100;
  double fitrange[2] = {30, 150};

  // plot options
  const char * plane_options[3] = {"U","V","Y"};
  const char * draw_options[10] = {"same", "SAME", "SAME", "SAME", "SAME", "SAME", "SAME", "SAME", "SAME", "SAME"};
  const int color_options[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 20};

  TString plotdir = getDir("Plots/");

  // input
  TFile *input = TFile::Open(Form("%s.root",FILENAME.Data()));

  TGraph *g1_eLifeVSRun_tpc0_plane2 = (TGraph*)input->Get("g1_eLifeVSRun_tpc0_plane2");
  TGraph *g1_eLifeVSRun_tpc1_plane2 = (TGraph*)input->Get("g1_eLifeVSRun_tpc1_plane2");
  TGraphErrors *g1_eLifeVSRun_tpc01_plane2 = (TGraphErrors*)input->Get("g1_eLifeVSRun_tpc01_plane2");

  TH1F *h1_trk_startx = (TH1F*)input->Get("h1_trk_startx");
  TH1F *h1_trk_starty = (TH1F*)input->Get("h1_trk_starty");
  TH1F *h1_trk_startz = (TH1F*)input->Get("h1_trk_startz");

  TH1F *h1_trk_endx = (TH1F*)input->Get("h1_trk_endx");
  TH1F *h1_trk_endy = (TH1F*)input->Get("h1_trk_endy");
  TH1F *h1_trk_endz = (TH1F*)input->Get("h1_trk_endz");


  TH1F *h1_trk_startx_selected = (TH1F*)input->Get("h1_trk_startx_selected");
  TH1F *h1_trk_starty_selected = (TH1F*)input->Get("h1_trk_starty_selected");
  TH1F *h1_trk_startz_selected = (TH1F*)input->Get("h1_trk_startz_selected");

  TH1F *h1_trk_endx_selected = (TH1F*)input->Get("h1_trk_endx_selected");
  TH1F *h1_trk_endy_selected = (TH1F*)input->Get("h1_trk_endy_selected");
  TH1F *h1_trk_endz_selected = (TH1F*)input->Get("h1_trk_endz_selected");

  TH1F *h1_trk_startx_tpc0_selected = (TH1F*)input->Get("h1_trk_startx_tpc0_selected");
  TH1F *h1_trk_starty_tpc0_selected = (TH1F*)input->Get("h1_trk_starty_tpc0_selected");
  TH1F *h1_trk_startz_tpc0_selected = (TH1F*)input->Get("h1_trk_startz_tpc0_selected");

  TH1F *h1_trk_endx_tpc0_selected = (TH1F*)input->Get("h1_trk_endx_tpc0_selected");
  TH1F *h1_trk_endy_tpc0_selected = (TH1F*)input->Get("h1_trk_endy_tpc0_selected");
  TH1F *h1_trk_endz_tpc0_selected = (TH1F*)input->Get("h1_trk_endz_tpc0_selected");

  TH1F *h1_trk_startx_tpc1_selected = (TH1F*)input->Get("h1_trk_startx_tpc1_selected");
  TH1F *h1_trk_starty_tpc1_selected = (TH1F*)input->Get("h1_trk_starty_tpc1_selected");
  TH1F *h1_trk_startz_tpc1_selected = (TH1F*)input->Get("h1_trk_startz_tpc1_selected");

  TH1F *h1_trk_endx_tpc1_selected = (TH1F*)input->Get("h1_trk_endx_tpc1_selected");
  TH1F *h1_trk_endy_tpc1_selected = (TH1F*)input->Get("h1_trk_endy_tpc1_selected");
  TH1F *h1_trk_endz_tpc1_selected = (TH1F*)input->Get("h1_trk_endz_tpc1_selected");


  TH1F *h1_trk_len = (TH1F*)input->Get("h1_trk_len");
  TH1F *h1_trk_len_selected = (TH1F*)input->Get("h1_trk_len_selected");
  TH1F *h1_trk_lenX = (TH1F*)input->Get("h1_trk_lenX");
  TH1F *h1_trk_lenX_selected = (TH1F*)input->Get("h1_trk_lenX_selected");

  TH1F *h1_ntrks_loop = (TH1F*)input->Get("h1_ntrks_loop");

  TH1F *h1_trk_thetaxz = (TH1F*)input->Get("h1_trk_thetaxz");
  TH1F *h1_trk_thetayz = (TH1F*)input->Get("h1_trk_thetayz");

  TH1F *h1_trk_thetaxz_with_cut = (TH1F*)input->Get("h1_trk_thetaxz_with_cut");
  TH1F *h1_trk_thetayz_with_cut = (TH1F*)input->Get("h1_trk_thetayz_with_cut");
  TH2F *h2_trk_angle = (TH2F*)input->Get("h2_trk_angle");
  TH2F *h2_trk_angle_with_cut = (TH2F*)input->Get("h2_trk_angle_with_cut");

  TH2F *h2_trk_startX_startY = (TH2F*)input->Get("h2_trk_startX_startY");
  TH2F *h2_trk_startX_startY_selected = (TH2F*)input->Get("h2_trk_startX_startY_selected");

  TH2F *h2_trk_startZ_startY = (TH2F*)input->Get("h2_trk_startZ_startY");
  TH2F *h2_trk_startZ_startY_selected = (TH2F*)input->Get("h2_trk_startZ_startY_selected");

  TH2F *h2_trk_start_end_y = (TH2F*)input->Get("h2_trk_start_end_y");


  TH2F *h2_dqdxhitpeakt_plane_2 = (TH2F*)input->Get("h2_dqdxhitpeakt_plane_2");

  TH1F* h1_s2n[3];
  TH1F* h1_s2n_aftercut[3];
  TH1F* h1_rms[3];
  TH1F* h1_t_maxpulseheight[3];

  TProfile2D *hp2d_angle[3];

  TH1F* h1_dqdx_tpc01_selected[3]; 
  TH1F* h1_dqdx_tpc01_selected_trunc[3]; 
  TH2F* h2_dqdxtime[3];
  TH2F* h2_dqdxX[3];
  TH2F* h2_dqdxX_tpc0[3];
  TH2F* h2_dqdxX_tpc1[3];
  TProfile2D *hp2d_angle_dqdx[3];

  TH2F* h2_dqdxhitpeakt_tpc0[3];
  TH2F* h2_dqdxhitpeakt_tpc1[3];
  TH2F* h2_dqdxhitpeakt_tpc01[3];

  TH2F* h2_dqdxhitpeakt_tpc0_trunc[3];
  TH2F* h2_dqdxhitpeakt_tpc1_trunc[3];
  TH2F* h2_dqdxhitpeakt_tpc01_trunc[3];


  for (int p=0; p<3; p++) {
    h1_s2n[p] = (TH1F*)input->Get(TString::Format("h1_s2n_plane_%d", p));
    h1_rms[p] = (TH1F*)input->Get(TString::Format("h1_rms_plane_%d", p)); 
    h1_t_maxpulseheight[p] = (TH1F*)input->Get(TString::Format("h1_t_maxpulseheight_plane_%d", p));

    h1_s2n_aftercut[p] = (TH1F*)input->Get(TString::Format("h1_s2n_aftercut_plane_%d", p));

    hp2d_angle[p] = (TProfile2D*)input->Get(TString::Format("hp2d_angle_plane_%d",p));
  
    h1_dqdx_tpc01_selected[p] = (TH1F*)input->Get(TString::Format("h1_dqdx_tpc01_plane_%d_selected",p));
    h1_dqdx_tpc01_selected_trunc[p] = (TH1F*)input->Get(TString::Format("h1_dqdx_tpc01_plane_%d_selected_trunc",p));
    h2_dqdxtime[p] = (TH2F*)input->Get(TString::Format("h2_dqdxtime_plane_%d",p));
    h2_dqdxX[p] = (TH2F*)input->Get(TString::Format("h2_dqdxX_plane_%d",p));
    h2_dqdxX_tpc0[p] = (TH2F*)input->Get(TString::Format("h2_dqdxX_tpc0_plane_%d",p));
    h2_dqdxX_tpc1[p] = (TH2F*)input->Get(TString::Format("h2_dqdxX_tpc1_plane_%d",p));
    
    hp2d_angle_dqdx[p] = (TProfile2D*)input->Get(TString::Format("hp2d_angle_dqdx_plane_%d",p));

    h2_dqdxhitpeakt_tpc0_trunc[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc0_plane_%d_trunc",p));
    h2_dqdxhitpeakt_tpc1_trunc[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc1_plane_%d_trunc",p));
    h2_dqdxhitpeakt_tpc01_trunc[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc01_plane_%d_trunc",p));

    h2_dqdxhitpeakt_tpc0[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc0_plane_%d",p));
    h2_dqdxhitpeakt_tpc1[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc1_plane_%d",p));
    h2_dqdxhitpeakt_tpc01[p] = (TH2F*)input->Get(TString::Format("h2_dqdxhitpeakt_tpc01_plane_%d",p));

  }
  
  //TH1F* h1_dqdxVSddist[3][nplots];
  TH1F* h1_dqdxVSddist_tpc0[3][nplots];
  TH1F* h1_dqdxVSddist_tpc1[3][nplots];
  TH1F* h1_dqdxVShpeaktime_tpc0[3][nplots];
  TH1F* h1_dqdxVShpeaktime_tpc1[3][nplots];
  TH1F* h1_dqdxVShpeaktime_tpc01[3][nplots];
  for (int n = 0; n < nplots; ++n){
    for (int ip = 0; ip < 3; ++ip){
      //h1_dqdxVSddist[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSddist_n_%d_plane_%d",n,ip));
      h1_dqdxVSddist_tpc0[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSddist_tpc0_n_%d_plane_%d",n,ip));
      h1_dqdxVSddist_tpc1[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSddist_tpc1_n_%d_plane_%d",n,ip));
      h1_dqdxVShpeaktime_tpc0[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSpeaktime_tpc0_n_%d_plane_%d",n,ip));
      h1_dqdxVShpeaktime_tpc1[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSpeaktime_tpc1_n_%d_plane_%d",n,ip));
      h1_dqdxVShpeaktime_tpc01[ip][n] = (TH1F*)input->Get(TString::Format("h1_dqdxVSpeaktime_n_%d_plane_%d",n,ip));
    }
  }

  ////////////////////////////////////////////////
  //NTracks
  TCanvas *c1_h1_ntrks_loop = new TCanvas("c1_h1_ntrks_loop", "c1_h1_ntrks_loop", 1200, 800);
  h1_ntrks_loop->GetXaxis()->SetRangeUser(0,30);
  h1_ntrks_loop->GetXaxis()->SetTitle("Loop Number");
  h1_ntrks_loop->GetYaxis()->SetTitle("Number of Tracks per Loop");
  h1_ntrks_loop->SetStats(0);
  h1_ntrks_loop->Draw("HIST");
  c1_h1_ntrks_loop->SaveAs(Form("%sh1_ntrks_loop.pdf",plotdir.Data()));

  //X start vs Y start
  TCanvas *c1_h2_trk_startX_startY = new TCanvas("c1_h2_trk_startX_startY", "c1_h2_trk_startX_startY", 1200, 800);
  h2_trk_startX_startY->Draw("COLZ");
  h2_trk_startX_startY->SetStats(0);
  c1_h2_trk_startX_startY->SaveAs(Form("%sh2_trk_startX_startY.pdf",plotdir.Data()));
  
  //X start vs Y start Selected
  TCanvas *c1_h2_trk_startX_startY_selected = new TCanvas("c1_h2_trk_startX_startY_selected", "c1_h2_trk_startX_startY_selected", 1200, 800);
  h2_trk_startX_startY_selected->Draw("COLZ");
  h2_trk_startX_startY_selected->SetStats(0);
  c1_h2_trk_startX_startY_selected->SaveAs(Form("%sh2_trk_startX_startY_selected.pdf",plotdir.Data()));

  //Z start vs Y start
  TCanvas *c1_h2_trk_startZ_startY = new TCanvas("c1_h2_trk_startZ_startY", "c1_h2_trk_startZ_startY", 1200, 800);
  h2_trk_startZ_startY->Draw("COLZ");
  h2_trk_startZ_startY->SetStats(0);
  c1_h2_trk_startZ_startY->SaveAs(Form("%sh2_trk_startZ_startY.pdf",plotdir.Data()));
  
  //Z start vs Y start Selected
  TCanvas *c1_h2_trk_startZ_startY_selected = new TCanvas("c1_h2_trk_startZ_startY_selected", "c1_h2_trk_startZ_startY_selected", 1200, 800);
  h2_trk_startZ_startY_selected->Draw("COLZ");
  h2_trk_startZ_startY_selected->SetStats(0);
  c1_h2_trk_startZ_startY_selected->SaveAs(Form("%sh2_trk_startZ_startY_selected.pdf",plotdir.Data()));

  //Y start vs Y end h2_trk_start_end_y
  TCanvas *c1_h2_trk_start_end_y = new TCanvas("c1_h2_trk_start_end_y", "c1_h2_trk_start_end_y", 1200, 800);
  h2_trk_start_end_y->Draw("COLZ");
  h2_trk_start_end_y->SetStats(0);
  c1_h2_trk_start_end_y->SaveAs(Form("%sh2_trk_start_end_y.pdf",plotdir.Data()));


  //h2_dqdxhitpeakt_plane_2-
/*
  TCanvas *c1_h2_dqdxhitpeakt_plane_2 = new TCanvas("c1_h2_dqdxhitpeakt_plane_2", "c1_h2_dqdxhitpeakt_plane_2", 1200, 800);
  h2_dqdxhitpeakt_plane_2->Draw("COLZ");
  h2_dqdxhitpeakt_plane_2->SetStats(0);
  h2_dqdxhitpeakt_plane_2->Fit("expo","","",10,180);
  TF1 *exp_plane2 = (TF1*)h2_dqdxhitpeakt_plane_2->GetListOfFunctions()->FindObject("expo");

  double mt = (exp_plane2->GetParameter(1));
  double errormt = exp_plane2->GetParError(1);

  double tlifetime = -(1/mt);

  double errortlife = tlifetime*(-1)*errormt/mt;
  cout <<  "FOR h2_dqdxhitpeakt_plane_2 " << Form("Electron Liftime is: %f +- %f",tlifetime,errortlife) << endl;
  TText* tlifetime_text = new TText(.5,.6,Form("Electron Liftime is: %f +- %f",tlifetime,errortlife));
  tlifetime_text->Draw("same");
  h2_dqdxhitpeakt_plane_2->SetTitle(Form("Run %s - Plane 2",RUNNUM.Data()));
  c1_h2_dqdxhitpeakt_plane_2->SaveAs(Form("%sh2_dqdxhitpeakt_plane_2.pdf",plotdir.Data()));
*/

  double mt, errormt, tlifetime, errortlife;
  for (int p = 0; p < 3; ++p){

      TCanvas *c1_h2_dqdxhitpeakt_tpc01 = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc01_plane_%d",p), Form("c1_h2_dqdxhitpeakt_tpc01_plane_%d",p), 1200, 800);
      h2_dqdxhitpeakt_tpc01[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc01[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc01[p]->Fit("expo","","",10,180);
      TF1 *exp01 = (TF1*)h2_dqdxhitpeakt_tpc01[p]->GetListOfFunctions()->FindObject("expo");
      if(exp01){ mt = (exp01->GetParameter(1)); errormt = exp01->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}

      TText* tlifetime_text01 = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text01->Draw("same");
      h2_dqdxhitpeakt_tpc01[p]->SetTitle(Form("Run %s - TPC 01 - Plane %d",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc01->SaveAs(Form("%sh2_dqdxhitpeakt_tpc01_plane_%d.pdf",plotdir.Data(),p));

      TCanvas *c1_h2_dqdxhitpeakt_tpc0 = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc0_plane_%d",p), Form("c1_h2_dqdxhitpeakt_tpc0_plane_%d",p), 1200, 800);
      h2_dqdxhitpeakt_tpc0[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc0[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc0[p]->Fit("expo","","",10,180);
      TF1 *exp0 = (TF1*)h2_dqdxhitpeakt_tpc0[p]->GetListOfFunctions()->FindObject("expo");
      if(exp0) {mt = (exp0->GetParameter(1)); errormt = exp0->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}
      TText* tlifetime_text0 = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text0->Draw("same");
      h2_dqdxhitpeakt_tpc0[p]->SetTitle(Form("Run %s - TPC 0 - Plane %d",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc0->SaveAs(Form("%sh2_dqdxhitpeakt_tpc0_plane_%d.pdf",plotdir.Data(),p));

      TCanvas *c1_h2_dqdxhitpeakt_tpc1 = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc1_plane_%d",p), Form("c1_h2_dqdxhitpeakt_tpc1_plane_%d",p), 1200, 800);
      h2_dqdxhitpeakt_tpc1[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc1[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc1[p]->Fit("expo","","",10,180);
      TF1 *exp1 = (TF1*)h2_dqdxhitpeakt_tpc1[p]->GetListOfFunctions()->FindObject("expo");
      if(exp1) {mt = (exp1->GetParameter(1)); errormt = exp1->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}
      
      TText* tlifetime_text1 = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text1->Draw("same");
      h2_dqdxhitpeakt_tpc1[p]->SetTitle(Form("Run %s - TPC 1 - Plane %d",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc1->SaveAs(Form("%sh2_dqdxhitpeakt_tpc1_plane_%d.pdf",plotdir.Data(),p));

      //Truncated Mean

      TCanvas *c1_h2_dqdxhitpeakt_tpc01_trunc = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc01_plane_%d_trunc",p), Form("c1_h2_dqdxhitpeakt_tpc01_plane_%d_trunc",p), 1200, 800);
      h2_dqdxhitpeakt_tpc01_trunc[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc01_trunc[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc01_trunc[p]->Fit("expo","","",10,180);
      TF1 *exp01_trunc = (TF1*)h2_dqdxhitpeakt_tpc01_trunc[p]->GetListOfFunctions()->FindObject("expo");
      if(exp01_trunc) {mt = (exp01_trunc->GetParameter(1)); errormt = exp01_trunc->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}
      
      TText* tlifetime_text01_trunc = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text01_trunc->Draw("same");
      h2_dqdxhitpeakt_tpc01_trunc[p]->SetTitle(Form("Run %s - TPC 01 - Plane %d Truncated",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc01_trunc->SaveAs(Form("%sh2_dqdxhitpeakt_tpc01_plane_%d_trunc.pdf",plotdir.Data(),p));

      TCanvas *c1_h2_dqdxhitpeakt_tpc0_trunc = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc0_plane_%d_trunc",p), Form("c1_h2_dqdxhitpeakt_tpc0_plane_%d_trunc",p), 1200, 800);
      h2_dqdxhitpeakt_tpc0_trunc[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc0_trunc[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc0_trunc[p]->Fit("expo","","",10,180);
      TF1 *exp0_trunc = (TF1*)h2_dqdxhitpeakt_tpc0_trunc[p]->GetListOfFunctions()->FindObject("expo");
      if(exp0_trunc) {mt = (exp0_trunc->GetParameter(1)); errormt = exp0_trunc->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}
      
      TText* tlifetime_text0_trunc = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text0_trunc->Draw("same");
      h2_dqdxhitpeakt_tpc0_trunc[p]->SetTitle(Form("Run %s - TPC 0 - Plane %d - Truncated",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc0_trunc->SaveAs(Form("%sh2_dqdxhitpeakt_tpc0_plane_%d_trunc.pdf",plotdir.Data(),p));

      TCanvas *c1_h2_dqdxhitpeakt_tpc1_trunc = new TCanvas(Form("c1_h2_dqdxhitpeakt_tpc1_plane_%d_trunc",p), Form("c1_h2_dqdxhitpeakt_tpc1_plane_%d_trunc",p), 1200, 800);
      h2_dqdxhitpeakt_tpc1_trunc[p]->Draw("COLZ");
      h2_dqdxhitpeakt_tpc1_trunc[p]->SetStats(0);
      h2_dqdxhitpeakt_tpc1_trunc[p]->Fit("expo","","",10,180);
      TF1 *exp1_trunc = (TF1*)h2_dqdxhitpeakt_tpc1_trunc[p]->GetListOfFunctions()->FindObject("expo");
      if(exp1_trunc) {mt = (exp1_trunc->GetParameter(1)); errormt = exp1_trunc->GetParError(1); tlifetime = -(1/mt); errortlife = tlifetime*(-1)*errormt/mt;}
      
      TText* tlifetime_text1_trunc = new TText(.5,.6,Form("Electron Liftime is: %2.2f us +- %2.2f",tlifetime,errortlife));
      tlifetime_text1_trunc->Draw("same");
      h2_dqdxhitpeakt_tpc1_trunc[p]->SetTitle(Form("Run %s - TPC 1 - Plane %d - Truncated",RUNNUM.Data(),p));
      c1_h2_dqdxhitpeakt_tpc1_trunc->SaveAs(Form("%sh2_dqdxhitpeakt_tpc1_plane_%d_trunc.pdf",plotdir.Data(),p));
      

  }
/*
  for (size_t tpc = 0; tpc < 2; ++tpc){
    TH2F *h2_dqdxhitpeakt_tpc_plane_2 = (TH2F*)input->Get(Form("h2_dqdxhitpeakt_tpc%d_plane_2",(int)tpc));
    h2_dqdxhitpeakt_tpc_plane_2->SetTitle(Form("TPC%d - Run %s - Plane 2",(int)tpc, RUNNUM.Data()));
    TCanvas *c1_h2_dqdxhitpeakt_tpc_plane_2 = new TCanvas("c1_h2_dqdxhitpeakt_tpc_plane_2", "c1_h2_dqdxhitpeakt_tpc_plane_2", 1200, 800);
    h2_dqdxhitpeakt_tpc_plane_2->Draw("COLZ");
    h2_dqdxhitpeakt_tpc_plane_2->SetStats(0);
    h2_dqdxhitpeakt_tpc_plane_2->Fit("expo","","",10,180);
    TF1 *exp_plane2 = (TF1*)h2_dqdxhitpeakt_tpc_plane_2->GetListOfFunctions()->FindObject("expo");
    double mt = (exp_plane2->GetParameter(1));
    double errormt = exp_plane2->GetParError(1);

    double tlifetime = -(1/mt);

    double errortlife = tlifetime*(-1)*errormt/mt;
    cout <<  Form("FOR: h2_dqdxhitpeakt_tpc%d_plane_2",(int)tpc) << Form("Electron Liftime is: %f +- %f",tlifetime,errortlife) << endl;
    
    c1_h2_dqdxhitpeakt_tpc_plane_2->SaveAs(Form("%sh2_dqdxhitpeakt_tpc%d_plane_2.pdf",plotdir.Data(),(int)tpc));
  }
*/

  // track start and end
  TCanvas *c1_start_end = new TCanvas("c1_start_end", "c1_start_end", 1200, 800);
  c1_start_end->Divide(3,2);
  
  c1_start_end->cd(1);
  h1_trk_startx->SetTitle("Start");
  h1_trk_startx->Draw();
  c1_start_end->cd(2);
  h1_trk_starty->SetTitle("Start");
  h1_trk_starty->Draw();
  c1_start_end->cd(3);
  h1_trk_startz->SetTitle("Start");
  h1_trk_startz->Draw();

  c1_start_end->cd(4);
  h1_trk_endx->SetTitle("End");
  h1_trk_endx->Draw();
  c1_start_end->cd(5);
  h1_trk_endy->SetTitle("End");
  h1_trk_endy->Draw();
  c1_start_end->cd(6);
  h1_trk_endz->SetTitle("End");
  h1_trk_endz->Draw();
  
  c1_start_end->SaveAs(Form("%strack_start_end.pdf",plotdir.Data()));


  TCanvas *c1_start_end_selected = new TCanvas("c1_start_end_selected", "c1_start_end_selected", 1200, 800);
  c1_start_end_selected->Divide(3,2);
  
  c1_start_end_selected->cd(1);
  h1_trk_startx_selected->SetTitle("Start");
  h1_trk_startx_selected->Draw();
  c1_start_end_selected->cd(2);
  h1_trk_starty_selected->SetTitle("Start");
  h1_trk_starty_selected->Draw();
  c1_start_end_selected->cd(3);
  h1_trk_startz_selected->SetTitle("Start");
  h1_trk_startz_selected->Draw();

  c1_start_end_selected->cd(4);
  h1_trk_endx_selected->SetTitle("End");
  h1_trk_endx_selected->Draw();
  c1_start_end_selected->cd(5);
  h1_trk_endy_selected->SetTitle("End");
  h1_trk_endy_selected->Draw();
  c1_start_end_selected->cd(6);
  h1_trk_endz_selected->SetTitle("End");
  h1_trk_endz_selected->Draw();
  
  c1_start_end_selected->SaveAs(Form("%strack_start_end_selected.pdf",plotdir.Data()));

  // track start and end TPC0
  TCanvas *c1_start_end_tpc0 = new TCanvas("c1_start_end_tpc0", "c1_start_end", 1200, 800);
  c1_start_end_tpc0->Divide(3,2);
  
  c1_start_end_tpc0->cd(1);
  h1_trk_startx_tpc0_selected->SetTitle("Start");
  h1_trk_startx_tpc0_selected->Draw();
  c1_start_end_tpc0->cd(2);
  h1_trk_starty_tpc0_selected->SetTitle("Start");
  h1_trk_starty_tpc0_selected->Draw();
  c1_start_end_tpc0->cd(3);
  h1_trk_startz_tpc0_selected->SetTitle("Start");
  h1_trk_startz_tpc0_selected->Draw();

  c1_start_end_tpc0->cd(4);
  h1_trk_endx_tpc0_selected->SetTitle("End");
  h1_trk_endx_tpc0_selected->Draw();
  c1_start_end_tpc0->cd(5);
  h1_trk_endy_tpc0_selected->SetTitle("End");
  h1_trk_endy_tpc0_selected->Draw();
  c1_start_end_tpc0->cd(6);
  h1_trk_endz_tpc0_selected->SetTitle("End");
  h1_trk_endz_tpc0_selected->Draw();
  
  c1_start_end_tpc0->SaveAs(Form("%strack_start_end_tpc0_selected.pdf",plotdir.Data()));

  // track start and end TPC1
  TCanvas *c1_start_end_tpc1 = new TCanvas("c1_start_end_tpc1", "c1_start_end", 1200, 800);
  c1_start_end_tpc1->Divide(3,2);
  
  c1_start_end_tpc1->cd(1);
  h1_trk_startx_tpc1_selected->SetTitle("Start");
  h1_trk_startx_tpc1_selected->Draw();
  c1_start_end_tpc1->cd(2);
  h1_trk_starty_tpc1_selected->SetTitle("Start");
  h1_trk_starty_tpc1_selected->Draw();
  c1_start_end_tpc1->cd(3);
  h1_trk_startz_tpc1_selected->SetTitle("Start");
  h1_trk_startz_tpc1_selected->Draw();

  c1_start_end_tpc1->cd(4);
  h1_trk_endx_tpc1_selected->SetTitle("End");
  h1_trk_endx_tpc1_selected->Draw();
  c1_start_end_tpc1->cd(5);
  h1_trk_endy_tpc1_selected->SetTitle("End");
  h1_trk_endy_tpc1_selected->Draw();
  c1_start_end_tpc1->cd(6);
  h1_trk_endz_tpc1_selected->SetTitle("End");
  h1_trk_endz_tpc1_selected->Draw();
  
  c1_start_end_tpc1->SaveAs(Form("%strack_start_end_tpc1_selected.pdf",plotdir.Data()));

  // track length
  TCanvas *c1_len = new TCanvas("c1_len", "c1_len", 800, 600);
  gPad->SetLogy();
  h1_trk_len->Draw();
  c1_len->SaveAs(Form("%strack_length.pdf",plotdir.Data()));

  TCanvas *c1_len_selected = new TCanvas("c1_len_selected", "c1_len_selected", 800, 600);
  gPad->SetLogy();
  h1_trk_len_selected->Draw();
  c1_len_selected->SaveAs(Form("%strack_lengthX_selected.pdf",plotdir.Data()));

// track lengthX
  TCanvas *c1_lenX = new TCanvas("c1_lenX", "c1_lenX", 800, 600);
  gPad->SetLogy();
  h1_trk_lenX->Draw();
  c1_lenX->SaveAs(Form("%strack_lengthX.pdf",plotdir.Data()));

  TCanvas *c1_len_selectedX = new TCanvas("c1_len_selectedX", "c1_len_selectedX", 800, 600);
  gPad->SetLogy();
  h1_trk_lenX_selected->Draw();
  c1_len_selectedX->SaveAs(Form("%strack_lengthX_selected.pdf",plotdir.Data()));


  // track angle
  TCanvas *c1_theta = new TCanvas("c1_theta", "c1_theta", 1200, 600);
  
  c1_theta->Divide(2,1);

  c1_theta->cd(1);
  //h1_trk_thetaxz->SetStats(0);
  h1_trk_thetaxz->Draw();

  c1_theta->cd(2);
  //h1_trk_thetayz->SetStats(0);
  h1_trk_thetayz->Draw();

  c1_theta->SaveAs(Form("%strack_angle_1d.pdf",plotdir.Data()));

  // track angle with cut
  TCanvas *c1_theta_cut = new TCanvas("c1_theta_cut", "c1_theta", 1200, 600);
  
  c1_theta_cut->Divide(2,1);

  c1_theta_cut->cd(1);
  //h1_trk_thetaxz_with_cut->SetStats(0);
  h1_trk_thetaxz_with_cut->Draw();

  c1_theta_cut->cd(2);
  //h1_trk_thetayz_with_cut->SetStats(0);
  h1_trk_thetayz_with_cut->Draw();

  c1_theta_cut->SaveAs(Form("%strack_angle_1d.pdf",plotdir.Data()));
  
  // h2
  TCanvas *c1_theta_2d = new TCanvas("c1_theta_2d", "c1_theta_2d", 800, 600);

  //h2_trk_angle->SetStats(0);
  h2_trk_angle->Draw("colz");
  
  c1_theta_2d->SaveAs(Form("%strack_angle_2d.pdf",plotdir.Data()));

  // h2
  TCanvas *c1_theta_cut_2d = new TCanvas("c1_theta_cut_2d", "c1_theta_2d", 800, 600);

  //h2_trk_angle->SetStats(0);
  h2_trk_angle_with_cut->Draw("colz");
  
  c1_theta_cut_2d->SaveAs(Form("%strack_angle_2d_cut.pdf",plotdir.Data()));

  // hp2d
  TCanvas *c1_theta_hp2d = new TCanvas("c1_theta_hp2d", "c1_theta_hp2d", 1200, 400);
  
  c1_theta_hp2d->Divide(3,1);

  for (int p=0; p<3; p++) {
    c1_theta_hp2d->cd(p+1);
    //hp2d_angle[p]->SetStats(0);
    hp2d_angle[p]->Draw("colz");
  }
  c1_theta_hp2d->SaveAs(Form("%strack_angle_sn2d.pdf",plotdir.Data()));



  
  // dqdx
/*
  TCanvas *c1_dqdx = new TCanvas("c1_dqdx", "c1_dqdx", 800, 600);
  auto lg_dqdx = new TLegend(0.7,0.7,0.9,0.9);
  for (int p=0; p<3; p++) {
    
    h1_dqdx[p]->SetStats(0);
    h1_dqdx[p]->GetXaxis()->SetRangeUser(0, 600.);
    h1_dqdx[p]->SetLineColor(5-color_options[p]);
    h1_dqdx[p]->SetLineWidth(2);
    h1_dqdx[p]->Draw(draw_options[p]);
    lg_dqdx->AddEntry(h1_dqdx[p], plane_options[p], "l");
  }
  lg_dqdx->Draw();
  c1_dqdx->SaveAs(Form("%sh1_dqdx.pdf",plotdir.Data()));
*/
  TCanvas *c1_dqdx_tpc01_selected = new TCanvas("c1_dqdx_selected", "c1_dqdx", 800, 600);
  auto lg_dqdx_tpc01_selected = new TLegend(0.7,0.7,0.9,0.9);
  for (int p=2; p<3; p++) {
    
    h1_dqdx_tpc01_selected[p]->SetStats(0);
    h1_dqdx_tpc01_selected[p]->GetXaxis()->SetRangeUser(0, 700.);
    h1_dqdx_tpc01_selected[p]->GetYaxis()->SetRangeUser(0, 2000.);
    h1_dqdx_tpc01_selected[p]->SetLineColor(5-color_options[p]);
    h1_dqdx_tpc01_selected[p]->SetLineWidth(2);
    h1_dqdx_tpc01_selected[p]->Draw(draw_options[p]);
    lg_dqdx_tpc01_selected->AddEntry(h1_dqdx_tpc01_selected[p], plane_options[p], "l");
  }
  lg_dqdx_tpc01_selected->Draw();
  c1_dqdx_tpc01_selected->SaveAs(Form("%sh1_dqdx_tpc01_selected.pdf",plotdir.Data()));

  TCanvas *c1_dqdx_tpc01_selected_trunc = new TCanvas("c1_dqdx_selected_trunc", "c1_dqdx", 800, 600);
  auto lg_dqdx_tpc01_selected_trunc = new TLegend(0.7,0.7,0.9,0.9);
  for (int p=2; p<3; p++) {
    
    h1_dqdx_tpc01_selected_trunc[p]->SetStats(0);
    h1_dqdx_tpc01_selected_trunc[p]->GetXaxis()->SetRangeUser(0, 700.);
    h1_dqdx_tpc01_selected_trunc[p]->GetYaxis()->SetRangeUser(0, 2000.);
    h1_dqdx_tpc01_selected_trunc[p]->SetLineColor(5-color_options[p]);
    h1_dqdx_tpc01_selected_trunc[p]->SetLineWidth(2);
    h1_dqdx_tpc01_selected_trunc[p]->Draw(draw_options[p]);
    lg_dqdx_tpc01_selected_trunc->AddEntry(h1_dqdx_tpc01_selected_trunc[p], plane_options[p], "l");
  }
  lg_dqdx_tpc01_selected_trunc->Draw();
  c1_dqdx_tpc01_selected_trunc->SaveAs(Form("%sh1_dqdx_tpc01_selected_trunc.pdf",plotdir.Data()));



  // dqdx vs time
  TCanvas *c1_dqdxtime[3];
  for (int p=0; p<3; p++) {
    
    c1_dqdxtime[p] = new TCanvas(TString::Format("c1_dqdxtime_plane_%d",p), TString::Format("c1_dqdxtime_plane_%d",p), 800, 600);
    h2_dqdxtime[p]->SetStats(0);
    h2_dqdxtime[p]->GetYaxis()->SetRangeUser(0, 600.);
    h2_dqdxtime[p]->Draw("colz");

    c1_dqdxtime[p]->SaveAs(TString::Format("%sh2_dqdxtime_plane_%d.pdf",plotdir.Data(),p));
  }

  // dqdx vs X
  TCanvas *c1_dqdxX[3];
  TCanvas *c1_dqdxX_tpc0[3];
  TCanvas *c1_dqdxX_tpc1[3];
  for (int p=0; p<3; p++) {
    
    c1_dqdxX[p] = new TCanvas(TString::Format("c1_dqdxX_plane_%d",p), TString::Format("c1_dqdxX_plane_%d",p), 800, 600);
    h2_dqdxX[p]->SetStats(0);
    h2_dqdxX[p]->GetYaxis()->SetRangeUser(0, 600.);
    h2_dqdxX[p]->Draw("colz");

    c1_dqdxX[p]->SaveAs(TString::Format("%sh2_dqdxX_plane_%d.pdf",plotdir.Data(),p));

    c1_dqdxX_tpc0[p] = new TCanvas(TString::Format("c1_dqdxX_tpc0_plane_%d",p), TString::Format("c1_dqdxX_tpc0_plane_%d",p), 800, 600);
    h2_dqdxX_tpc0[p]->SetStats(0);
    h2_dqdxX_tpc0[p]->GetYaxis()->SetRangeUser(0, 600.);
    h2_dqdxX_tpc0[p]->Draw("colz");

    c1_dqdxX_tpc0[p]->SaveAs(TString::Format("%sh2_dqdxX_tpc0_plane_%d.pdf",plotdir.Data(),p));

    c1_dqdxX_tpc1[p] = new TCanvas(TString::Format("c1_dqdxX_tpc1_plane_%d",p), TString::Format("c1_dqdxX_tpc1_plane_%d",p), 800, 600);
    h2_dqdxX_tpc1[p]->SetStats(0);
    h2_dqdxX_tpc1[p]->GetYaxis()->SetRangeUser(0, 600.);
    h2_dqdxX_tpc1[p]->Draw("colz");

    c1_dqdxX_tpc1[p]->SaveAs(TString::Format("%sh2_dqdxX_tpc1_plane_%d.pdf",plotdir.Data(),p));
  }

  // angle dqdx
  TCanvas *c1_angle_dqdx[3];

  for (int p=0; p<3; p++) {
    
    c1_angle_dqdx[p] = new TCanvas(TString::Format("c1_angle_dqdx_plane_%d",p), TString::Format("c1_angle_dqdx_plane_%d",p), 800, 600);
    //hp2d_angle_dqdx[p]->SetStats(0);
    hp2d_angle_dqdx[p]->Draw("colz");

    c1_angle_dqdx[p]->SaveAs(TString::Format("%shp2d_angle_dqdx_plane_%d.pdf",plotdir.Data(),p));
  }
  double vd = 0.148; // cm/us
  double m, tau0, tau1;
  

  TCanvas *c1_dqdxVShpeaktime_tpc0[3][nplots];
  TCanvas *c1_dqdxVShpeaktime_tpc1[3][nplots];
  TCanvas *c1_dqdxVShpeaktime_tpc01[3][nplots];
  for (int n = 0; n < nplots; ++n){
    for (int ip = 0; ip < 3; ++ip){
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime_tpc0[ip][n])) continue;
      if(h1_dqdxVShpeaktime_tpc0[ip][n]->GetEntries() == 0) continue;
      c1_dqdxVShpeaktime_tpc0[ip][n] = new TCanvas(TString::Format("h1_dqdxVShpeaktime_tpc0_n_%d_plane_%d",n,ip), TString::Format("h1_dqdxVShpeaktime_tpc0_n_%d_plane_%d",n,ip), 800, 600);
      //TF1 *f1 = new TF1("f1","expo",-40,0);
      
      //TF1 *gfit = (TF1 *)h1_dqdxVSddist[ip][n]->GetFunction("expo");
      //TF1 *fit = h1_dqdxVSddist[ip][n]->GetFunction(function_name)
      h1_dqdxVShpeaktime_tpc0[ip][n]->Fit("expo","Q","",fitrange[0],fitrange[1]);
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime_tpc0[ip][n]->GetListOfFunctions()->FindObject("expo");
      
      
      //exp->SetLineColor(5);
      //exp->SetLineStyle(2);
      h1_dqdxVShpeaktime_tpc0[ip][n]->Draw("hist E");
      
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m = (exp->GetParameter(1));
        tau0 = -(1/m);
        //cout << "TPC1: Electron Liftime is: " << tau0 << " us on plane: " << ip << endl;
        exp->Draw("same");
        TText* taut = new TText(.5,.6,Form(" Electron Liftime is: %f",tau0));
        taut->Draw("same");
      }
      h1_dqdxVShpeaktime_tpc0[ip][n]->SetTitle(Form("Run %s - TPC0 - Plane2 n=%d",RUNNUM.Data(), n));
      c1_dqdxVShpeaktime_tpc0[ip][n]->SaveAs(TString::Format("%sh1_dqdxVShpeaktime_tpc0_n_%d_plane_%d.pdf",plotdir.Data(),n,ip));

    }
  }
  for (int n = 0; n < nplots; ++n){
    for (int ip = 0; ip < 3; ++ip){
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime_tpc1[ip][n])) continue;
      if(h1_dqdxVShpeaktime_tpc1[ip][n]->GetEntries() == 0) continue;
      c1_dqdxVShpeaktime_tpc1[ip][n] = new TCanvas(TString::Format("h1_dqdxVShpeaktime_tpc1_n_%d_plane_%d",n,ip), TString::Format("h1_dqdxVShpeaktime_tpc1_n_%d_plane_%d",n,ip), 800, 600);
      //TF1 *f1 = new TF1("f1","expo",-40,0);
      
      //TF1 *gfit = (TF1 *)h1_dqdxVSddist[ip][n]->GetFunction("expo");
      //TF1 *fit = h1_dqdxVSddist[ip][n]->GetFunction(function_name)
      h1_dqdxVShpeaktime_tpc1[ip][n]->Fit("expo","Q","",fitrange[0],fitrange[1]);
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime_tpc1[ip][n]->GetListOfFunctions()->FindObject("expo");
      
      
      //exp->SetLineColor(5);
      //exp->SetLineStyle(2);
      h1_dqdxVShpeaktime_tpc1[ip][n]->Draw("hist E");
      
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m = (exp->GetParameter(1));
        tau1 = -(1/m);
        //cout << "TPC1: Electron Liftime is: " << tau1 << " us on plane: " << ip << endl;
        exp->Draw("same");
        double er = pow(tau1,2)*exp->GetParError(1);
        TText* taut = new TText(.5,.6,Form(" Electron Liftime is: %f +- %f",tau1,er));
        taut->Draw("same");
      }
      h1_dqdxVShpeaktime_tpc1[ip][n]->SetTitle(Form("Run %s - TPC1 - Plane2 n=%d",RUNNUM.Data(),n));
      c1_dqdxVShpeaktime_tpc1[ip][n]->SaveAs(TString::Format("%sh1_dqdxVShpeaktime_tpc1_n_%d_plane_%d.pdf",plotdir.Data(),n,ip));

    }
  }
  for (int n = 0; n < nplots; ++n){
    for (int ip = 0; ip < 3; ++ip){
      if(ip != 2) continue;
      if(!(h1_dqdxVShpeaktime_tpc01[ip][n])) continue;
      if(h1_dqdxVShpeaktime_tpc01[ip][n]->GetEntries() == 0) continue;
      c1_dqdxVShpeaktime_tpc01[ip][n] = new TCanvas(TString::Format("h1_dqdxVShpeaktime_tpc01_n_%d_plane_%d",n,ip), TString::Format("h1_dqdxVShpeaktime_tpc01_n_%d_plane_%d",n,ip), 800, 600);
      //TF1 *f1 = new TF1("f1","expo",-40,0);
      
      //TF1 *gfit = (TF1 *)h1_dqdxVSddist[ip][n]->GetFunction("expo");
      //TF1 *fit = h1_dqdxVSddist[ip][n]->GetFunction(function_name)
      h1_dqdxVShpeaktime_tpc01[ip][n]->Fit("expo","Q","",fitrange[0],fitrange[1]);
      TF1 *exp = (TF1*)h1_dqdxVShpeaktime_tpc01[ip][n]->GetListOfFunctions()->FindObject("expo");
      
      
      //exp->SetLineColor(5);
      //exp->SetLineStyle(2);
      h1_dqdxVShpeaktime_tpc01[ip][n]->Draw("hist E");
      
      if(exp){
        //cout<<"fitting f(x) = exp(p0+p1*x)"<<endl;
        //cout<<"p0: "<< exp->GetParameter(0)<<endl;
        //cout<<"p1: "<< exp->GetParameter(1)<<endl;
        //cout<<""<<endl;
        m = (exp->GetParameter(1));
        tau1 = -(1/m);
        //cout << "TPC1: Electron Liftime is: " << tau1 << " us on plane: " << ip << endl;
        exp->Draw("same");
        double er = pow(tau1,2)*exp->GetParError(1);
        TText* taut = new TText(.5,.6,Form(" Electron Liftime is: %f #pm %f",tau1,er));
        taut->Draw("same");
      }
      h1_dqdxVShpeaktime_tpc01[ip][n]->SetTitle(Form("Run %s - TPC 01 - Plane2 n=%d",RUNNUM.Data(),n));
      c1_dqdxVShpeaktime_tpc01[ip][n]->SaveAs(TString::Format("%sh1_dqdxVShpeaktime_tpc01_n_%d_plane_%d.pdf",plotdir.Data(),n,ip));

    }
  }

  //Plot Lifetimes vs Run
  TCanvas* graph_eLifeVSRun_tpc0_plane2 = new TCanvas("graph_eLifeVSRun_tpc0_plane2","graph_eLifeVSRun_tpc0_plane2",800, 600);
  g1_eLifeVSRun_tpc0_plane2->Draw("A*");
  //g1_eLifeVSRun_tpc0_plane2->GetYaxis()->SetRangeUser(0,120);
  graph_eLifeVSRun_tpc0_plane2->SaveAs(TString::Format("%seLifeVSRun_tpc0_plane2.pdf",plotdir.Data()));
  
  TCanvas* graph_eLifeVSRun_tpc1_plane2 = new TCanvas("graph_eLifeVSRun_tpc1_plane2","graph_eLifeVSRun_tpc1_plane2",800, 600);
  g1_eLifeVSRun_tpc1_plane2->Draw("A*");
  //g1_eLifeVSRun_tpc1_plane2->GetYaxis()->SetRangeUser(0,120);
  graph_eLifeVSRun_tpc1_plane2->SaveAs(TString::Format("%seLifeVSRun_tpc1_plane2.pdf",plotdir.Data()));

  TCanvas* graph_eLifeVSRun_tpc01_plane2 = new TCanvas("graph_eLifeVSRun_tpc01_plane2","graph_eLifeVSRun_tpc01_plane2",800, 600);
  g1_eLifeVSRun_tpc01_plane2->SetTitle(Form("Run %s Electron Lifetime - Plane 2",RUNNUM.Data()));
  g1_eLifeVSRun_tpc01_plane2->SetMarkerStyle(11);
  g1_eLifeVSRun_tpc01_plane2->Draw("AP");

  g1_eLifeVSRun_tpc01_plane2->GetYaxis()->SetRangeUser(0,2500);
  //g1_eLifeVSRun_tpc01_plane2->GetXaxis()->SetRangeUser(6000,7000);
  graph_eLifeVSRun_tpc01_plane2->SaveAs(TString::Format("%seLifeVSRun_tpc01_plane2.pdf",plotdir.Data()));
  



}


