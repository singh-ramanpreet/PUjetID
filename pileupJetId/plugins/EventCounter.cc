#include "PUjetID/pileupJetId/plugins/EventCounter.h"

using namespace reco;

EventCounter::EventCounter(edm::ParameterSet const& cfg): 
  pupInfoToken(consumes<edm::View<PileupSummaryInfo> >(edm::InputTag("slimmedAddPileupInfo"))),
  genEvtInfoToken(consumes<GenEventInfoProduct>(edm::InputTag("generator"))),
  genParticlesToken(consumes<edm::View<reco::GenParticle> >(edm::InputTag("prunedGenParticles")))
{
}
//////////////////////////////////////////////////////////////////////////////////////////
void EventCounter::beginJob() 
{
  evtWtHisto_       = fs_->make<TH1F>("GenEventWeight","GenEventWeight",1,-0.5,0.5);
  puHisto_          = fs_->make<TH1F>("pileup","pileup",100,0,100);
}
//////////////////////////////////////////////////////////////////////////////////////////
void EventCounter::endJob() 
{  
}
//////////////////////////////////////////////////////////////////////////////////////////
void EventCounter::analyze(edm::Event const& iEvent, edm::EventSetup const& iSetup) 
{
  int npu(0);
  if (!iEvent.isRealData()) { 
    iEvent.getByToken(genEvtInfoToken,genEvtInfo);
    iEvent.getByToken(pupInfoToken,pupInfo);
    iEvent.getByToken(genParticlesToken,genParticles);

    evtWtHisto_->Fill(0.0,genEvtInfo->weight());
    edm::View<PileupSummaryInfo>::const_iterator PUI;

    for(PUI = pupInfo->begin(); PUI != pupInfo->end(); ++PUI) {
      if (PUI->getBunchCrossing() == 0) {
        npu = PUI->getTrueNumInteractions();
      }
    }
    puHisto_->Fill(npu,genEvtInfo->weight());
  }
  else {
    evtWtHisto_->Fill(0.0,1);
    puHisto_->Fill(0.0);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////
EventCounter::~EventCounter() 
{
}

DEFINE_FWK_MODULE(EventCounter);
