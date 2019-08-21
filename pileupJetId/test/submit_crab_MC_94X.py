from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-MC-cfg_94X.py'

config.JobType.outputFiles = ['mc_flatTree.root']
config.JobType.maxJobRuntimeMin = 120
#config.JobType.maxMemoryMB = 6400

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/jets_2017_inc/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = [
        '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', #48675378
#        '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017RECOSIMstep_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #49125561
#        '/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #34859434
#        '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #9701595
#        '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM', #1149467
#        '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM', #4346952
        ]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2017_' + dataset.split("/")[1].split("_")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
