from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-MC-cfg.py'

config.JobType.outputFiles = ['mc_flatTree.root']
#config.JobType.maxMemoryMB = 6400

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/%s/jets_2017/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = ['/DY1JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM',
                 '/DY2JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM',
                 '/DY3JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM',
                 '/DY4JetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM']

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2017_' + dataset.split("/")[1].split("_")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
