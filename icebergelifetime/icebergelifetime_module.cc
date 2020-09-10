////////////////////////////////////////////////////////////////////////
// Class:       icebergelifetime
// Plugin Type: analyzer (art v3_05_01)
// File:        icebergelifetime_module.cc
//
// Generated at Mon Aug 17 17:25:52 2020 by Ivan Caro Terrazas using cetskelgen
// from cetlib version v3_10_00.
////////////////////////////////////////////////////////////////////////

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Handle.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Principal/SubRun.h"
#include "canvas/Utilities/InputTag.h"
#include "fhiclcpp/ParameterSet.h"
#include "messagefacility/MessageLogger/MessageLogger.h"

#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art_root_io/TFileService.h"
#include "art_root_io/TFileDirectory.h"
#include "canvas/Persistency/Common/FindManyP.h"
#include "lardata/Utilities/AssociationUtil.h"

#include "larcore/Geometry/Geometry.h"
#include "nusimdata/SimulationBase/MCTruth.h"
#include "nusimdata/SimulationBase/MCFlux.h"
#include "nusimdata/SimulationBase/MCParticle.h"
#include "lardataobj/Simulation/SimChannel.h"
#include "lardataobj/Simulation/AuxDetSimChannel.h"
#include "lardataobj/AnalysisBase/Calorimetry.h"
#include "lardataobj/AnalysisBase/ParticleID.h"
#include "lardataobj/RawData/RawDigit.h"
#include "lardataobj/RawData/raw.h"
#include "lardataobj/RawData/BeamInfo.h"
#include "lardataobj/RecoBase/PFParticle.h"
#include "lardataobj/RecoBase/TrackHitMeta.h"
#include "lardata/Utilities/AssociationUtil.h"
#include "lardata/DetectorInfoServices/DetectorPropertiesService.h"
#include "larcoreobj/SummaryData/POTSummary.h"
#include "larsim/MCCheater/BackTrackerService.h"
#include "larsim/MCCheater/ParticleInventoryService.h"
#include "lardataobj/RecoBase/Track.h"
#include "lardataobj/RecoBase/Cluster.h"
#include "lardataobj/RecoBase/Hit.h"
#include "lardataobj/RecoBase/Wire.h"
#include "lardataobj/RecoBase/EndPoint2D.h"
#include "lardataobj/RecoBase/Vertex.h"
#include "lardataobj/RecoBase/OpFlash.h"
#include "larcoreobj/SimpleTypesAndConstants/geo_types.h"
#include "larreco/RecoAlg/TrackMomentumCalculator.h"
#include "lardataobj/AnalysisBase/CosmicTag.h"
#include "lardataobj/AnalysisBase/FlashMatch.h"
#include "lardataobj/AnalysisBase/T0.h"
#include "lardataobj/AnalysisBase/BackTrackerMatchingData.h"
#include "larevt/SpaceChargeServices/SpaceChargeService.h"
#include "larevt/CalibrationDBI/Interface/ChannelStatusService.h"
#include "larevt/CalibrationDBI/Interface/ChannelStatusProvider.h"

#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TMinuit.h"
#include "TString.h"
#include "TTimeStamp.h"

using namespace std;


const int kMaxTracks = 1000;
const int kMaxHits = 1000;


class icebergelifetime;


class icebergelifetime : public art::EDAnalyzer {
public:
  explicit icebergelifetime(fhicl::ParameterSet const& p);
  // The compiler-generated destructor is fine for non-base
  // classes without bare pointers or other resource use.

  // Plugins should not be copied or assigned.
  icebergelifetime(icebergelifetime const&) = delete;
  icebergelifetime(icebergelifetime&&) = delete;
  icebergelifetime& operator=(icebergelifetime const&) = delete;
  icebergelifetime& operator=(icebergelifetime&&) = delete;

  // Required functions.
  void analyze(art::Event const& e) override;

  // Selected optional functions.
  void beginJob() override;
  void endJob() override;

private:

  // Declare member data here.
  std::string fHitModuleLabel;
  std::string fTrackModuleLabel;
  std::string fCalorimetryModuleLabel;
  bool fSaveRawWaveForm;
  std::vector<int> fSelectedWires;

  // reset
  void reset();

  // TTree
  TTree *fEventTree;

  // event information
  int event;
  int run;
  int subrun;
  double evttime;
  int year_month_date;
  int hour_min_sec;

  // track
  int ntrks;
  float vdrift;
  int trkid[kMaxTracks];
  float trkminx[kMaxTracks][3];
  float trkstart[kMaxTracks][3];

  float trkend[kMaxTracks][3];
  float trklen[kMaxTracks];
  float trkphi[kMaxTracks];
  float trktheta[kMaxTracks];
  float trkthetaxz[kMaxTracks];
  float trkthetayz[kMaxTracks];
  float trkstartcosxyz[kMaxTracks][3];
  float trkendcosxyz[kMaxTracks][3];

  // lifetime
  int ntrkhits[kMaxTracks][3];
  float trkpitchvec[kMaxTracks][3][kMaxHits];
  float trkdqdx[kMaxTracks][3][kMaxHits];
  float trkx[kMaxTracks][3][kMaxHits];
  float trkxNoCorr[kMaxTracks][3][kMaxHits];
  float trkt[kMaxTracks][3][kMaxHits];
  float trkhitpeakt[kMaxTracks][3][kMaxHits];
  int nplane[kMaxTracks][3][kMaxHits];

  // hit
  //double trkhitx[kMaxTracks][3][kMaxHits];
  //double trkhity[kMaxTracks][3][kMaxHits];
  //double trkhitz[kMaxTracks][3][kMaxHits];

  //int wireid[kMaxTracks][kMaxHits];
  //int chid[kMaxTracks][kMaxHits];
  //int tpcid[kMaxTracks][kMaxHits];
  //float hit_plane[kMaxTracks][kMaxHits];

  //double cosgma[kMaxTracks][kMaxHits];

  //std::vector<std::vector< double > >* _trkdqdx_v; 

  // waveform
  int fNticks; 
  int fNticksReadout;
  float fSampleRate;

};


icebergelifetime::icebergelifetime(fhicl::ParameterSet const& p)
  : EDAnalyzer{p}  // ,
  // More initializers here.
{
  // Call appropriate consumes<>() for any products to be retrieved by this module.
  fHitModuleLabel         = p.get<std::string>("HitModuleLabel");
  fTrackModuleLabel       = p.get<std::string>("TrackModuleLabel");
  fCalorimetryModuleLabel = p.get<std::string>("CalorimetryModuleLabel");
  fSaveRawWaveForm        = p.get<bool>("SaveRawWaveForm");
  fSelectedWires          = p.get<std::vector<int>>("SelectedWires");

  //produces<art::Assns<recob::Hit, anab::Calorimetry>>();

  // DetectorPropertiesService
  auto const *detprop = lar::providerFrom<detinfo::DetectorPropertiesService>();
  fNticks = detprop->NumberTimeSamples(); // number of clock ticks per event
  fNticksReadout = detprop->ReadOutWindowSize(); // number of clock ticks per readout window
  fSampleRate = detprop->SamplingRate(); // period of the TPC readout electronics clock

  cout << "Numer of clock ticks per event: " << fNticks << endl;
  cout << "Numer of clock ticks per readout window: " << fNticksReadout << endl;
  cout << "Sampling rate: " << fSampleRate << endl;
  cout << "Using fCalorimetryModuleLabel = " << fCalorimetryModuleLabel << endl;
}

void icebergelifetime::analyze(art::Event const& e)
{
  // Implementation of required member function here.
  reset();
  // event info
  run = e.run();
  subrun = e.subRun();
  event = e.id().event();
  art::Timestamp ts = e.time();
  TTimeStamp tts(ts.timeHigh(), ts.timeLow());
  evttime = tts.AsDouble();
  

  //cout << "tts " << tts << endl;
  //cout << "evttime " << evttime << endl;

  UInt_t year=0;
  UInt_t month=0;
  UInt_t day=0;

  year_month_date=tts.GetDate(kTRUE,0,&year,&month,&day);

  UInt_t hour=0;
  UInt_t min=0;
  UInt_t sec=0;

  hour_min_sec=tts.GetTime(kTRUE,0,&hour,&min,&sec);


  // channel status
  //lariov::ChannelStatusProvider const& channelStatus
  //  = art::ServiceHandle<lariov::ChannelStatusService const>()->GetProvider();

  // hit
  art::Handle< std::vector<recob::Hit> > hitListHandle;
  std::vector< art::Ptr<recob::Hit> > hitlist;
  if (e.getByLabel(fHitModuleLabel, hitListHandle)) {
    art::fill_ptr_vector(hitlist, hitListHandle);
  }

//if(event.getByLabel("hitpdune", hitListHandle)) art::fill_ptr_vector(hitlist, hitListHandle);

  // track
  art::Handle< std::vector<recob::Track> > trackListHandle;
  std::vector< art::Ptr<recob::Track> > tracklist;
  if (e.getByLabel(fTrackModuleLabel,trackListHandle)) {
    art::fill_ptr_vector(tracklist, trackListHandle);
  }

  art::ServiceHandle<geo::Geometry> geom;

  art::FindManyP<recob::Hit> fmtrkhit(trackListHandle, e, fTrackModuleLabel);
  art::FindManyP<anab::Calorimetry> fmtrkcalo(trackListHandle, e, fCalorimetryModuleLabel);
  //art::FindManyP<raw::RawDigit> fmhitrawdigit(hitListHandle, e, fHitModuleLabel);
  //art::FindManyP<recob::Wire> fmhitwire(hitListHandle, e, fHitModuleLabel);
  //art::FindManyP<raw::RawDigit> fmwirerawdigit(wireListHandle, e, "digitwire");
  art::FindManyP<recob::Hit, recob::TrackHitMeta> fmhittrkmeta(trackListHandle, e, fTrackModuleLabel);
  


  auto const *detprop = lar::providerFrom<detinfo::DetectorPropertiesService>();

  
  ntrks = 0;
  for (const auto& trk : tracklist) {
    if(ntrks >= kMaxTracks) break;
    vdrift = detprop->DriftVelocity()*1e-3;
    trkid[ntrks] = trk->ID();
    trklen[ntrks] = trk->Length();
    trkphi[ntrks] = trk->Phi();
    trktheta[ntrks] = trk->Theta();

    // TVector3
    auto start = trk->Vertex();
    auto end = trk->End();
    auto start_dir = trk->VertexDirection();
    auto end_dir = trk->EndDirection();

    trkthetaxz[ntrks] = std::atan2(start_dir.X(), start_dir.Z());
    trkthetayz[ntrks]= std::atan2(start_dir.Y(), start_dir.Z());
    
    trkstart[ntrks][0] = start.X();
    trkstart[ntrks][1] = start.Y();
    trkstart[ntrks][2] = start.Z();

    trkend[ntrks][0] = end.X();
    trkend[ntrks][1] = end.Y();
    trkend[ntrks][2] = end.Z();

    trkstartcosxyz[ntrks][0] = start_dir.X();
    trkstartcosxyz[ntrks][1] = start_dir.Y();
    trkstartcosxyz[ntrks][2] = start_dir.Z();

    trkendcosxyz[ntrks][0] = end_dir.X();
    trkendcosxyz[ntrks][1] = end_dir.Y();
    trkendcosxyz[ntrks][2] = end_dir.Z();

    // calometry
    if (fmtrkcalo.isValid()) {
      std::vector<art::Ptr<anab::Calorimetry>> calos = fmtrkcalo.at(ntrks);
      //std::vector<art::Ptr<recob::Hit>> rhits = fmtrkhit.at(ntrks);
      //std::vector<art::Assns<recob::Hit, anab::Calorimetry> > caloshits = 
      //std::auto_ptr< art::Assns<anab::Calorimetry, recob::Hit> > assn(new art::Assns<anab::Calorimetry, recob::Hit>);

      //cout << "Start Calo loop, calos size = "<< calos.size() << " and rhits size =  " << rhits.size() << ", for trk " << ntrks << endl;
      for (size_t icalo=0; icalo<calos.size(); icalo++) {// loops over planes , n = 3
        if (!calos[icalo]) continue;
        if (!calos[icalo]->PlaneID().isValid) continue;
        int planenum = calos[icalo]->PlaneID().Plane;
        if (planenum<0 || planenum>2) continue;
        //cout << "Looking at Plane " << planenum << endl; 
        const size_t NHits = calos[icalo] -> dEdx().size();
        if(NHits > kMaxHits) continue;
        ntrkhits[ntrks][planenum] = NHits;
        //cout << TString::Format("ntrkhits[%d][%d] = ",ntrks,planenum) << ntrkhits[ntrks][planenum] << endl;

        //Loop through hits to find min X
        double minx = 1e9; double minpht = 1e9;
        for (size_t iHit=0; iHit<NHits; ++iHit) {
          //cout << "(calos[icalo]->TrkPitchVec())[iHit]" << (calos[icalo]->TrkPitchVec())[iHit] << endl; 
          trkpitchvec[ntrks][planenum][iHit] = (calos[icalo]->TrkPitchVec())[iHit];
          if ((calos[icalo]->TrkPitchVec())[iHit]>1) continue;
          const auto& TrkPos = (calos[icalo] -> XYZ())[iHit];
          if (TrkPos.X() < minx){
            minx = TrkPos.X();
            //cout << minx << endl;
          }
          size_t tpIndex=(calos[icalo]->TpIndices()[iHit]);
          if (hitlist[tpIndex]->Multiplicity()>1) continue;
          if(hitlist[tpIndex]->PeakTime()*(500./1000.f) < minpht){
            minpht = hitlist[tpIndex]->PeakTime()*(500./1000.f); //in microseconds
          }
        }// End loop hits

        trkminx[ntrks][planenum] = (float) minx;
        
        for(size_t iHit = 0; iHit < NHits; ++iHit) {

          if ((calos[icalo]->TrkPitchVec())[iHit]>1) continue;
          const auto& TrkPos1 = (calos[icalo] -> XYZ())[iHit];
          size_t tpIndex=(calos[icalo]->TpIndices()[iHit]);
          if (hitlist[tpIndex]->Multiplicity()>1) continue;
          trkhitpeakt[ntrks][planenum][iHit]=hitlist[tpIndex]->PeakTime()*(500./1000.f) - minpht; //in microsec

          
          trkxNoCorr[ntrks][planenum][iHit] = TrkPos1.X();
          double x = TrkPos1.X() - minx; //subtract the minx to get correct t0
          double XDriftVelocity = detprop->DriftVelocity()*1e-3; //cm/ns
          //XDriftVelocity = 0.148/1000. ; //OVERWRITE for lartpc at 92% nominal field; ONLY RUN4
          double t = x/(XDriftVelocity*1000); //change the velocity units from cm/ns to cm/us
          trkx[ntrks][planenum][iHit] = x;
          trkt[ntrks][planenum][iHit] = t;
          trkdqdx[ntrks][planenum][iHit] = (calos[icalo]->dQdx())[iHit];
          //cout << Form("trkhitpeakt[%d][%d][%d] = ",ntrks,planenum,(int) iHit) << trkhitpeakt[ntrks][planenum][iHit] << ", t = " << t << endl;
          nplane[ntrks][planenum][iHit] = planenum;
        }// end loop hits

      } // end loop over icalo
    
    } //  end if fmtrkcalo

    // hits associated with trk
/*
    std::vector<art::Ptr<recob::Hit>> allhits = fmtrkhit.at(ntrks); // use either trk.key() or ntrks 
    
    for (size_t ihit=0; ihit<allhits.size(); ihit++) {
      // wire plane information
      unsigned int wireplane = allhits[ihit]->WireID().Plane;
      if (wireplane <0 || wireplane>2) continue;
      unsigned int wire = allhits[ihit]->WireID().Wire;
      unsigned int tpc = allhits[ihit]->WireID().TPC;
      unsigned int channel = allhits[ihit]->Channel();
     
      if (channelStatus.IsBad(channel)) continue;

      // hit position: not all hits are associated with space points, using neighboring space points to interpolate
      
      double xyz[3] = {-9999.0, -9999.0, -9999.0};
      bool fBadhit = false;

      if (fmhittrkmeta.isValid()) {
        auto vhit = fmhittrkmeta.at(ntrks);
        auto vmeta = fmhittrkmeta.data(ntrks);

        for (size_t ii=0; ii<vhit.size(); ii++) {
          if (vhit[ii].key() == allhits[ihit].key()) {
            
            if (vmeta[ii]->Index() == std::numeric_limits<int>::max()) {
              fBadhit = true;
              continue;
            }

            if (vmeta[ii]->Index() >= trk->NumberTrajectoryPoints()) {
              throw cet::exception("Calorimetry_module.cc") << "Requested track trajectory index "<<vmeta[ii]->Index()<<" exceeds the total number of trajectory points "<<trk->NumberTrajectoryPoints()<<" for track index "<<ntrks<<". Something is wrong with the track reconstruction. Please contact tjyang@fnal.gov!!";
            }

            if (!trk->HasValidPoint(vmeta[ii]->Index())) {
              fBadhit = true;
              continue;
            }
            
            auto loc = trk->LocationAtPoint(vmeta[ii]->Index());
            xyz[0] = loc.X();
            xyz[1] = loc.Y();
            xyz[2] = loc.Z();
            
            break;
          } // if (vhit[ii].key() == allhits[ihit].key())
        
        } // end of for ii

      } // if fmhittrkmeta.isValid()

      if (fBadhit) continue;
      
      //trkhitx[ntrks][wireplane][ihit] = xyz[0];
      //trkhity[ntrks][wireplane][ihit] = xyz[1];
      //trkhitz[ntrks][wireplane][ihit] = xyz[2];
      
      wireid[ntrks][ihit] = wire;
      chid[ntrks][ihit] = channel;
      tpcid[ntrks][ihit] = tpc;
      hit_plane[ntrks][ihit] = wireplane;

      // calculate track angle w.r.t. wire
      double angleToVert = geom->WireAngleToVertical(geom->View(allhits[ihit]->WireID()), allhits[ihit]->WireID().TPC, allhits[ihit]->WireID().Cryostat)-0.5*::util::pi<>();
      const auto& dir = trk->DirectionAtPoint(0);
      // angleToVert: return the angle w.r.t y+ axis, anti-closewise
      // dir: 3d track direction: u = (x,y,z);
      // vector that perpendicular to wires in yz plane v = (0, sin(angleToVert), cos(angleToVert))   
      // cos gamma = u.Dot(v)/(u.mag()*v.mag()) here, u.mag()=v.mag()=1
      double tmp_cosgamma = abs(sin(angleToVert)*dir.Y() + std::cos(angleToVert)*dir.Z());
      cosgma[ntrks][ihit] = tmp_cosgamma;
      
    }
    */
    ntrks++;
    if(ntrks > kMaxTracks) break;

  }
  fEventTree->Fill();
}

void icebergelifetime::beginJob()
{
  // Implementation of optional member function here.
  art::ServiceHandle<art::TFileService> tfs;
  fEventTree = tfs->make<TTree>("Event", "Event");
  fEventTree->Branch("event", &event, "event/I");
  fEventTree->Branch("run", &run, "run/I");
  fEventTree->Branch("subrun", &subrun, "subrun/I");
  fEventTree->Branch("evttime", &evttime, "evttime/D");
  fEventTree->Branch("year_month_date", &year_month_date, "year_month_date/I");
  fEventTree->Branch("hour_min_sec", &hour_min_sec, "hour_min_sec/I");
  fEventTree->Branch("vdrift", &vdrift, "vdrift/D");
  
  // track
  fEventTree->Branch("ntrks", &ntrks, "ntrks/I");
  fEventTree->Branch("trkid", trkid, "trkid[ntrks]/I");
  fEventTree->Branch("trkstart", trkstart, "trkstart[ntrks][3]/F");
  fEventTree->Branch("trkend", trkend, "trkend[ntrks][3]/F");
  fEventTree->Branch("trklen", trklen, "trklen[ntrks]/F");
  fEventTree->Branch("trkphi", trkphi, "trkphi[ntrks]/F");
  fEventTree->Branch("trktheta", trktheta, "trktheta[ntrks]/F");
  fEventTree->Branch("trkthetaxz", trkthetaxz, "trkthetaxz[ntrks]/F");
  fEventTree->Branch("trkthetayz", trkthetayz, "trkthetayz[ntrks]/F");
  fEventTree->Branch("trkstartcosxyz", trkstartcosxyz, "trkstartcosxyz[ntrks][3]/F");
  fEventTree->Branch("trkendcosxyz", trkendcosxyz, "trkendcosxyz[ntrks][3]/F");
  fEventTree->Branch("trkminx", &trkminx, "trkminx[ntrks][3]/F");
  fEventTree->Branch("ntrkhits", ntrkhits, "ntrkhits[ntrks][3]/I");

  fEventTree->Branch("trkdqdx", trkdqdx, "trkdqdx[ntrks][3][1000]/F");
  fEventTree->Branch("trkhitpeakt", trkhitpeakt, "trkhitpeakt[ntrks][3][1000]/F");
  fEventTree->Branch("trkpitchvec", trkpitchvec, "trkpitchvec[ntrks][3][1000]/F");
  fEventTree->Branch("trkxNoCorr", trkxNoCorr, "trkxNoCorr[ntrks][3][1000]/F");
  //fEventTree->Branch("trkdedx", trkdedx, "trkdedx[ntrks][3][1000]/F");
  fEventTree->Branch("trkx", trkx, "trkx[ntrks][3][1000]/F");
  fEventTree->Branch("trkt", trkt, "trkt[ntrks][3][1000]/F");
  fEventTree->Branch("nplane", nplane, "nplane[ntrks][3][1000]/I");

  // hit
  //fEventTree->Branch("trkhitx", trkhitx, "trkhitx[ntrks][3][700]/D");
  //fEventTree->Branch("trkhity", trkhity, "trkhity[ntrks][3][700]/D");
  //fEventTree->Branch("trkhitz", trkhitz, "trkhitz[ntrks][3][700]/D");
  
}

void icebergelifetime::endJob()
{
  // Implementation of optional member function here.
}
void icebergelifetime::reset(){
  run = -99999;
  subrun = -99999;
  event = -99999;
  evttime = -99999;
  year_month_date = -99999;
  hour_min_sec = -99999;
  vdrift = -9999.;

  
  ntrks = -99999;
  for (size_t i=0; i<kMaxTracks; ++i) {
    trkid[i] = -1;
    trklen[i] = -1.0;
    trkphi[i] = -10.0;
    trktheta[i] = -10.0;
    trkthetaxz[i] = -9999.0;
    trkthetayz[i] = -9999.0;
    
    for (int j=0; j<3; j++) {
      trkstart[i][j] = -9999.0;
      trkend[i][j] = -9999.0;
      trkstartcosxyz[i][j] = -9999.0;
      trkendcosxyz[i][j] = -9999.0;
      
      ntrkhits[i][j] = -9999;
      trkminx[i][j] = -9999.0;
      for (int k=0; k<kMaxHits; k++) {
        trkpitchvec[i][j][k] = -9999.0;
        //trkhitx[i][j][k] = -9999.0;
        //trkhity[i][j][k] = -9999.0;
        //trkhitz[i][j][k] = -9999.0;

        trkdqdx[i][j][k] = -9999.0;
        trkhitpeakt[i][j][k] = -9999.0;
        nplane[i][j][k] = -1;
        //trkdedx[i][j][k] = -9999.0;
        trkx[i][j][k] = -9999.0;
        trkxNoCorr[i][j][k] = -9999.0;
        trkt[i][j][k] = -9999.0;
      }
    }
  }
}


DEFINE_ART_MODULE(icebergelifetime)
