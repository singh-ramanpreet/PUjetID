from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-MC-cfg_UL2017.py'

config.JobType.outputFiles = ['mc_flatTree.root']
config.JobType.maxJobRuntimeMin = 120
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL17_V4_MC.db']

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 5
config.Data.outLFNDirBase = '/store/user/singhr/jme_ntuplesUL/'
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = [
        '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM', #101077576
#        '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #182359906
#        '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', #48675378
#        '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #49125561
        ]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2017_' + dataset.split("/")[1].split("_")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
