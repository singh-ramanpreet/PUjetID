import FWCore.ParameterSet.Config as cms 
process = cms.Process('myprocess')
process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_flatTree.root'))
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.GlobalTag.globaltag = '102X_upgrade2018_realistic_v20'

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
  "/store/mc/RunIIAutumn18MiniAOD/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/102X_upgrade2018_realistic_v15-v1/90000/F06E680B-364E-F94F-89D7-0374C51C2A5B.root"
  )
)
#############   Format MessageLogger #################
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#--- re-apply JEC from the GT -------------------------
process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")

process.patJetCorrFactorsReapplyJEC = process.updatedPatJetCorrFactors.clone(
  src = cms.InputTag("slimmedJets"),
  levels = ['L1FastJet','L2Relative','L3Absolute'],
  payload = 'AK4PFchs' 
)

process.patJetCorrFactorsReapplyJECPuppi = process.updatedPatJetCorrFactors.clone(
  src = cms.InputTag("slimmedJetsPuppi"),
  levels = ['L1FastJet','L2Relative','L3Absolute'],
  payload = 'AK4PFPuppi'
)

process.patJetsReapplyJEC = process.updatedPatJets.clone(
  jetSource = cms.InputTag("slimmedJets"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
)

process.patJetsReapplyJECPuppi = process.updatedPatJets.clone(
  jetSource = cms.InputTag("slimmedJetsPuppi"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJECPuppi"))
)

#--- define the good jets -------------------------------
from PhysicsTools.PatAlgos.selectionLayer1.jetSelector_cfi import selectedPatJets
process.goodJets = selectedPatJets.clone(src='patJetsReapplyJEC', cut='pt > 10 && abs(eta) < 5.0')
process.goodJetsPuppi = selectedPatJets.clone(src='patJetsReapplyJECPuppi', cut='pt > 10 && abs(eta) < 5.0')

#---- Tight JetID -----------------------------------------------------
tight_abs_eta_2p6_chs_puppi = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.90 && numberOfDaughters > 1)
&& (chargedHadronEnergyFraction > 0 && chargedMultiplicity > 0) && abs(eta) <= 2.6)"""

tight_abs_eta_2p6_2p7_chs = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.99 && chargedMultiplicity > 0)  && abs(eta) > 2.6 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_chs = """(neutralEmEnergyFraction > 0.02 && neutralEmEnergyFraction < 0.99 && neutralMultiplicity > 2
&& abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_chs = """(neutralHadronEnergyFraction > 0.02 && neutralEmEnergyFraction < 0.90 && neutralMultiplicity > 10 && abs(eta) > 3.0 )"""

tight_abs_eta_2p6_2p7_puppi = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.99)  && abs(eta) > 2.6 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_puppi = """(neutralHadronEnergyFraction < 0.99 && abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_puppi = """(neutralHadronEnergyFraction > 0.02 && neutralEmEnergyFraction < 0.90
&& neutralMultiplicity > 2 && neutralMultiplicity < 15 && abs(eta) > 3.0 )"""

process.tightIdJets = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJets"),
        cut = cms.string(tight_abs_eta_2p6_chs_puppi + " || " + tight_abs_eta_2p6_2p7_chs + " || " + tight_abs_eta_2p7_3p0_chs + " || " + tight_abs_eta_3p0_chs)
        )

process.tightIdJetsPuppi = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJetsPuppi"),
        cut = cms.string(tight_abs_eta_2p6_chs_puppi + "||" + tight_abs_eta_2p6_2p7_puppi + " || " + tight_abs_eta_2p7_3p0_puppi + " || " + tight_abs_eta_3p0_puppi)
        )

#--- define the pileup id -------------------------------
#from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_102x
process.load("RecoJets.JetProducers.PileupJetID_cfi")
process.pileupJetId.jets = cms.InputTag("tightIdJets")
process.pileupJetId.inputIsCorrected = True
process.pileupJetId.applyJec = False
process.pileupJetId.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices") 
#process.pileupJetId.algos = cms.VPSet(_chsalgos_102x)

process.pileupJetIdPuppi = process.pileupJetId.clone(jets = "tightIdJetsPuppi")

##-------------------- User analyzers  --------------------------------
process.jmechs            = cms.EDAnalyzer('JMEFlatTreeProducer',
  jets                    = cms.InputTag('tightIdJets'),
  muons                   = cms.InputTag('slimmedMuons'),
  electrons               = cms.InputTag('slimmedElectrons'),
  met                     = cms.InputTag('slimmedMETs'),
  vertices                = cms.InputTag('offlineSlimmedPrimaryVertices'),
  pileupJetId             = cms.InputTag('pileupJetId'),
  pileupJetIdFlag         = cms.InputTag('pileupJetId:fullId'),
  pileupJetIdDiscriminant = cms.InputTag('pileupJetId:fullDiscriminant'),
  rho                     = cms.InputTag('fixedGridRhoFastjetAll'),
  btagger                 = cms.string('pfCombinedInclusiveSecondaryVertexV2BJetTags'),
  triggerNames            = cms.vstring(
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v'
  ),
  triggerResults   = cms.InputTag('TriggerResults','','HLT'),
  triggerPrescales = cms.InputTag('patTrigger'),
  minLepPt         = cms.double(20),
  maxLepEta        = cms.double(2.4),
  minLLMass        = cms.double(70),
  maxLLMass        = cms.double(110),
  isMC             = cms.untracked.bool(True),
  genjets          = cms.untracked.InputTag('slimmedGenJets')
)

process.jmepuppi = process.jmechs.clone(
  jets                    = "tightIdJetsPuppi",
  met                     = "slimmedMETsPuppi",
  pileupJetId             = "pileupJetIdPuppi",
  pileupJetIdFlag         = "pileupJetIdPuppi:fullId",
  pileupJetIdDiscriminant = "pileupJetIdPuppi:fullDiscriminant"
)

process.eventCounter = cms.EDAnalyzer("EventCounter")

process.p = cms.Path(
   process.eventCounter +
   process.patJetCorrFactorsReapplyJEC +
   process.patJetCorrFactorsReapplyJECPuppi +
   process.patJetsReapplyJEC +
   process.patJetsReapplyJECPuppi +
   process.goodJets +
   process.goodJetsPuppi +
   process.tightIdJets +
   process.tightIdJetsPuppi +
   process.pileupJetId +
   process.pileupJetIdPuppi +
   process.jmechs +
   process.jmepuppi
)
