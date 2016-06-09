# import ROOT in batch mode                                                                                                                                                                                                                  
import sys                                                                                                                                                                                                                                   
oldargv = sys.argv[:]                                                                                                                                                                                                                        
sys.argv = [ '-b-' ]                                                                                                                                                                                                                         
import ROOT                                                                                                                                                                                                                                                                    
ROOT.gROOT.SetBatch(True)                                                                                                                                                                                                                                                      
sys.argv = oldargv                                                                                                                                                                                                                                                             
                                                                                                                                                                                                                                                                               
# load FWLite C++ libraries                                                                                                                                                                                                                                                    
ROOT.gSystem.Load("libFWCoreFWLite.so");                                                                                                                                                                                                                                       
ROOT.gSystem.Load("libDataFormatsFWLite.so");                                                                                                                                                                                                                                  
ROOT.AutoLibraryLoader.enable()                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                               
# load FWlite python libraries                                                                                                                                                                                                                                                 
from DataFormats.FWLite import Handle, Events                                                                                                                                                                                                                                  
from PhysicsTools.HeppyCore.utils.deltar import deltaR
                                                                                                                                                                                                                                                                               
#slimmedJets, slimmedJetLabel = Handle("std::vector<pat::Jet>"), "slimmedJets"                                                                                                                                                                                                                
jets, jetLabel = Handle("std::vector<pat::Jet>"), "updatedJets"                                                                                                                                                                                                                
pujetids, pujetidLabel = Handle("edm::ValueMap<StoredPileupJetIdentifier>"), "pileupJetIdUpdated"                                                                                                                                                                                                                
pujetidDiscriminant, pujetidDiscriminantLabel = Handle("edm::ValueMap<float>") , "pileupJetIdUpdated:fullDiscriminant"                                                                                                                                                                                                                                                                                                                                          
pujetidFullId, pujetidFullIdLabel = Handle("edm::ValueMap<int>") , "pileupJetIdUpdated:fullId"                                                                                                                                                                                                                                                                                                                                          
vertices, vertexLabel = Handle("std::vector<reco::Vertex>"), "offlineSlimmedPrimaryVertices"                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                        
# open file (you can use 'edmFileUtil -d /store/whatever.root' to get the physical file name)                                                                                                                                                                                                                                                                                               
events = Events("file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/patTupleUpdatedFromMiniAODzmm2.root")
                   
#eff_loose=0
#eff_test=0
#eff_medium=0
#eff_tight=0
#num_jets=0
		                                                                                                                                                                                                                                                                                                                                                                            
for iev,event in enumerate(events):                                                                                                                                                                                                                                                                                                                                                         
    #if iev >= 10: break                                                                                                                                                                                                                                                                                                                                                                     
    #event.getByLabel(slimmedJetLabel, slimmedJets)                                                                                                                                                                                                                                                                                                                                                        
    event.getByLabel(jetLabel, jets)                                                                                                                                                                                                                                                                                                                                                        
    event.getByLabel(pujetidLabel, pujetids)                                                                                                                                                                                                                                                                                                                                                        
    event.getByLabel(pujetidDiscriminantLabel, pujetidDiscriminant)                                                                                                                                                                                                                                                                                                                                                        
    event.getByLabel(pujetidFullIdLabel, pujetidFullId)   
    event.getByLabel(vertexLabel, vertices)                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                            
    print "\nEvent %d: run %6d, lumi %4d, event %12d" % (iev,event.eventAuxiliary().run(), event.eventAuxiliary().luminosityBlock(),event.eventAuxiliary().event())                                                                                                                                                                                                                         
           
    print len(vertices.product())
    #if len(vertices.product())<15: continue
	                                                                                                                                                                                                                                                                                                                                                                                    
    # Jets (standard AK4)
    for i,j in enumerate(jets.product()):
        if j.pt() < 20 or abs(j.eta())>1: continue
	#print "slimmedJet", j.pt(), j.pt()*j.jecFactor('Uncorrected')
        print "jet %3d: pt %5.1f (raw pt %5.1f, matched-calojet pt %5.1f), eta %+4.2f, pileup mva disc %+.2f" % (
            i, j.pt(), j.pt()*j.jecFactor('Uncorrected'), j.userFloat("caloJetMap:pt"), j.eta(), j.userFloat("pileupJetIdUpdated:fullDiscriminant"))
        print "Passes loose: ", bool(pujetidFullId.product().get(i) & (1 << 2)), "medium: ", bool(pujetidFullId.product().get(i) & (1 << 1)), "tight: ", bool(pujetidFullId.product().get(i) & (1 << 0))
        string=""
        string+="MVA=%.3f, " % (pujetidDiscriminant.product().get(i))
        variables=['RMS', 'beta', 'betaClassic', 'betaStar', 'betaStarClassic', 'dR2Mean', 'dRMatch', 'dRMean', 'dZ', 'frac01', 'frac02', 'frac03', 'frac04', 'frac05', 'frac06', 'frac07', 'jetEta', 'jetPt', 'jetR', 'jetRchg', 'majW', 'minW', 'nCharged', 'nNeutrals', 'nParticles', 'nTrueInt', 'nvtx', 'ptD', 'pull', 'rho']
        for var in variables:
          string+=var+"=%.4f, " % (getattr(pujetids.product().get(i),var)())
        print string
        #try: genJetMatch=deltaR(j.genJet().eta(),j.genJet().phi(),j.eta(),j.phi())<0.2 and ((abs(j.partonFlavour()) > 0 and abs(j.partonFlavour()) < 6) or (j.partonFlavour() == 21))
        #except: genJetMatch=0
        #if genJetMatch:
        #    num_jets+=1.
        #    eff_loose+=bool(pujetidFullId.product().get(i) & (1 << 2))
        #    eff_medium+=bool(pujetidFullId.product().get(i) & (1 << 1))
        #    eff_tight+=bool(pujetidFullId.product().get(i) & (1 << 0))

#print num_jets
#print eff_test/num_jets
#print eff_loose/num_jets
#print eff_medium/num_jets
#print eff_tight/num_jets
