import FWCore.ParameterSet.Config as cms

process = cms.Process("PATUPDATE")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
#  fileNames = cms.untracked.vstring(["file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/0018ACA9-77C4-E511-B438-C4346BBC1498.root"])
#  fileNames = cms.untracked.vstring(["file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/06532BBC-05C8-E511-A60A-F46D043B3CE5.root"])
#  fileNames = cms.untracked.vstring(["/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/06532BBC-05C8-E511-A60A-F46D043B3CE5.root"])
  fileNames = cms.untracked.vstring(["/store/relval/CMSSW_7_6_4/RelValZMM_13/MINIAODSIM/76X_mcRun2_asymptotic_v14_reHLTtest2-v1/10000/58882EB9-EEED-E511-8A66-0CC47A4D767E.root",
                                     "/store/relval/CMSSW_7_6_4/RelValZMM_13/MINIAODSIM/76X_mcRun2_asymptotic_v14_reHLTtest2-v1/10000/66085DE3-EEED-E511-B0F6-0025905AA9CC.root"])
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
print process.pileupJetIdUpdated.dumpConfig()

process.load("PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff")
process.patJetCorrFactorsReapplyJEC = process.updatedPatJetCorrFactors.clone(
  src = cms.InputTag("slimmedJets"),
  levels = ['L1FastJet', 'L2Relative', 'L3Absolute'] )
process.updatedJets = process.updatedPatJets.clone(
  jetSource = cms.InputTag("slimmedJets"),
  jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC"))
  )
process.updatedJets.userData.userFloats.src += ['pileupJetIdUpdated:fullDiscriminant']

process.p = cms.Path( process.pileupJetIdUpdated + process.patJetCorrFactorsReapplyJEC + process. updatedJets )

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/patTupleUpdatedFromMiniAODzmm2.root"),
    outputCommands = cms.untracked.vstring('keep *')
    )

process.endpath = cms.EndPath(process.out)
