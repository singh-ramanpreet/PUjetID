import FWCore.ParameterSet.Config as cms 
process = cms.Process('myprocess')
process.TFileService=cms.Service("TFileService",fileName=cms.string('mc_flatTree.root'))
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

import FWCore.ParameterSet.VarParsing as VarParsing
options = VarParsing.VarParsing ('analysis')
options.register('isAPV', 0, VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.int)
options.register('ptcut', '10', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string)
options.parseArguments()
isAPV = options.isAPV
ptcut = options.ptcut
print(isAPV, ptcut)

if not isAPV:
    process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_preVFP_v9'
    file_string = 'Summer19UL16'
else:
    process.GlobalTag.globaltag = '106X_mcRun2_asymptotic_v15'
    file_string = 'Summer19UL16APV'

from CondCore.CondDB.CondDB_cfi import CondDB
CondDBJECFile = CondDB.clone(connect = cms.string('sqlite:%s_V5_MC.db' % file_string))
process.jec = cms.ESSource(
    'PoolDBESSource', CondDBJECFile,
    toGet = cms.VPSet(
        cms.PSet(record = cms.string('JetCorrectionsRecord'),
                 tag = cms.string('JetCorrectorParametersCollection_%s_V5_MC_AK4PFchs' % file_string),
                 label = cms.untracked.string('AK4PFchs')),
        cms.PSet(record = cms.string('JetCorrectionsRecord'),
                 tag = cms.string('JetCorrectorParametersCollection_%s_V5_MC_AK4PFPuppi' % file_string),
                 label = cms.untracked.string('AK4PFPuppi'))
    )
)

##-------------------- Define the source  ----------------------------
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
  "root://cmsxrootd.fnal.gov//store/mc/RunIISummer19UL16MiniAOD/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/MINIAODSIM/106X_mcRun2_asymptotic_v13-v2/100000/02AEA966-DF0D-7647-95A1-97B73C3D7AF3.root"
  )
)
#############   Format MessageLogger #################
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

#--- re-apply JEC from the GT -------------------------
process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")

# Add an ESPrefer to override JEC that might be available from the global tag
process.es_prefer_jec = cms.ESPrefer('PoolDBESSource', 'jec')

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
process.goodJets = selectedPatJets.clone(src='patJetsReapplyJEC', cut='pt > %s && abs(eta) < 5.0' % ptcut)
process.goodJetsPuppi = selectedPatJets.clone(src='patJetsReapplyJECPuppi', cut='pt > %s && abs(eta) < 5.0' % ptcut)

#---- Tight JetID -----------------------------------------------------
tight_abs_eta_2p4_chs_puppi = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.90 && numberOfDaughters > 1)
&& (chargedHadronEnergyFraction > 0 && chargedMultiplicity > 0) && abs(eta) <= 2.4)"""

tight_abs_eta_2p4_2p7_chs = """((neutralHadronEnergyFraction < 0.90 && neutralEmEnergyFraction < 0.99)  && abs(eta) > 2.4 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_chs = """(neutralEmEnergyFraction > 0.0 && neutralEmEnergyFraction < 0.99 && neutralMultiplicity > 1
&& abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_chs = """(neutralHadronEnergyFraction > 0.2 && neutralEmEnergyFraction < 0.90 && neutralMultiplicity > 10 && abs(eta) > 3.0 )"""

tight_abs_eta_2p4_2p7_puppi = """((neutralHadronEnergyFraction < 0.98 && neutralEmEnergyFraction < 0.99)  && abs(eta) > 2.4 && abs(eta) <= 2.7)"""

tight_abs_eta_2p7_3p0_puppi = """(neutralMultiplicity >= 1 && abs(eta) > 2.7 && abs(eta) <= 3.0 )"""

tight_abs_eta_3p0_puppi = """(neutralEmEnergyFraction < 0.90 && neutralMultiplicity > 2 && abs(eta) > 3.0 )"""

process.tightIdJets = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJets"),
        cut = cms.string(tight_abs_eta_2p4_chs_puppi + " || " + tight_abs_eta_2p4_2p7_chs + " || " + tight_abs_eta_2p7_3p0_chs + " || " + tight_abs_eta_3p0_chs)
        )

process.tightIdJetsPuppi = cms.EDFilter("PATJetSelector",
        src = cms.InputTag("goodJetsPuppi"),
        cut = cms.string(tight_abs_eta_2p4_chs_puppi + "||" + tight_abs_eta_2p4_2p7_puppi + " || " + tight_abs_eta_2p7_3p0_puppi + " || " + tight_abs_eta_3p0_puppi)
        )

#--- define the pileup id -------------------------------
#from RecoJets.JetProducers.PileupJetID_cfi import _chsalgos_94x
process.load("RecoJets.JetProducers.PileupJetID_cfi")
process.pileupJetId.jets = cms.InputTag("tightIdJets")
process.pileupJetId.inputIsCorrected = True
process.pileupJetId.applyJec = False
process.pileupJetId.vertexes = cms.InputTag("offlineSlimmedPrimaryVertices") 
#process.pileupJetId.algos = cms.VPSet(_chsalgos_94x)


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
    'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v'
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