# This configuration is an example that recalibrates the slimmedJets from MiniAOD
# and adds a new userfloat "oldJetMass" to it

import FWCore.ParameterSet.Config as cms

process = cms.Process("PATUPDATE")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(["/store/relval/CMSSW_7_6_4/RelValZMM_13/AODSIM/76X_mcRun2_asymptotic_v14_reHLTtest2-v1/10000/1E24713C-EAED-E511-9F55-0CC47A78A42E.root",
                                     "/store/relval/CMSSW_7_6_4/RelValZMM_13/AODSIM/76X_mcRun2_asymptotic_v14_reHLTtest2-v1/10000/F4D2F62C-EAED-E511-9C83-0CC47A4D7678.root"
                                     ])
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
#process.source.skipEvents = cms.untracked.uint32(8)

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '76X_mcRun2_asymptotic_RunIIFall15DR76_v1')

#from CondCore.DBCommon.CondDBSetup_cfi import *
#import os
#era = "Fall15_25nsV2_MC"
#dBFile = era+".db"
#print "\nUsing private SQLite file", dBFile, "\n"
#process.jec = cms.ESSource("PoolDBESSource",CondDBSetup,
#    		connect = cms.string( "sqlite_file:"+dBFile ),
#    		toGet =  cms.VPSet(
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PF"),
#    				label= cms.untracked.string("AK4PF")
#    				),
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFchs"),
#    				label= cms.untracked.string("AK4PFchs")
#    				),
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK4PFPuppi"),
#    				label= cms.untracked.string("AK4PFPuppi")
#    				),
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK8PF"),
#    				label= cms.untracked.string("AK8PF")
#    				),
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK8PFchs"),
#    				label= cms.untracked.string("AK8PFchs")
#    				),
#    			cms.PSet(
#    				record = cms.string("JetCorrectionsRecord"),
#    				tag = cms.string("JetCorrectorParametersCollection_"+era+"_AK8PFPuppi"),
#    				label= cms.untracked.string("AK8PFPuppi")
#    				),
#    			)
#    		)
#
#process.es_prefer_jec = cms.ESPrefer("PoolDBESSource",'jec')

process.load("RecoJets.JetProducers.PileupJetID_cfi")
process.pileupJetId.jets=cms.InputTag("ak4PFJetsCHS")
process.pileupJetId.inputIsCorrected=False
process.pileupJetId.applyJec=True
process.pileupJetId.vertexes=cms.InputTag("offlinePrimaryVertices")
print process.pileupJetId.dumpConfig()

process.p = cms.Path(process.pileupJetId)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string("file:////afs/cern.ch/user/h/hinzmann/workspace/tmp/patTupleUpdatedFromAODzmm.root"),
    outputCommands = cms.untracked.vstring('keep *')
    )

process.endpath = cms.EndPath(process.out)

