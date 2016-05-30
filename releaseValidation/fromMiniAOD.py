import FWCore.ParameterSet.Config as cms

process = cms.Process("PATUPDATE")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
#  fileNames = cms.untracked.vstring(["file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/0018ACA9-77C4-E511-B438-C4346BBC1498.root"])
#  fileNames = cms.untracked.vstring(["file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/06532BBC-05C8-E511-A60A-F46D043B3CE5.root"])
#  fileNames = cms.untracked.vstring(["root://xrootd.unl.edu//store/relval/CMSSW_7_6_2/RelValTTbar_13/MINIAODSIM/PU25ns_76X_mcRun2_asymptotic_v12-v1/00000/DC900947-DC9C-E511-B3AC-0CC47A4C8F0A.root"])
  fileNames = cms.untracked.vstring(["/store/relval/CMSSW_7_6_2/RelValZMM_13/MINIAODSIM/PU25ns_76X_mcRun2_asymptotic_v12-v1/00000/C86BA73E-D09C-E511-AD68-002590596468.root"])
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )
#process.source.skipEvents = cms.untracked.uint32(8)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_RunIIFall15DR76_v1')

process.load("RecoJets.JetProducers.PileupJetID_cfi")
process.pileupJetIdUpdated = process.pileupJetId.clone(
  jets=cms.InputTag("slimmedJets"),
  inputIsCorrected=True,
  applyJec=True,
  vertexes=cms.InputTag("offlineSlimmedPrimaryVertices")
  )
print process.pileupJetId.dumpConfig()

process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
process.patJetCorrFactorsReapplyJEC = process.patJetCorrFactorsUpdated.clone(
  src = cms.InputTag("slimmedJets"),
  levels = ['L1FastJet', 'L2Relative', 'L3Absolute'] )
process.updatedJets = process.patJetsUpdated.clone(
  jetSource = cms.InputTag("slimmedJets"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
  )
process.updatedJets.userData.userFloats.src += ['pileupJetIdUpdated:fullDiscriminant']

process.p = cms.Path( process.pileupJetIdUpdated + process.patJetCorrFactorsReapplyJEC + process. updatedJets )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/patTupleUpdatedFromMiniAODzmm.root"),
    outputCommands = cms.untracked.vstring('keep *')
    )

process.endpath = cms.EndPath(process.out)
