from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-MC-cfg_UL2018.py'

config.JobType.outputFiles = ['mc_flatTree.root']
config.JobType.maxJobRuntimeMin = 120
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL18_V5_MC.db']

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
        #'/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer19UL18MiniAOD-106X_upgrade2018_realistic_v11_L1v1-v1/MINIAODSIM', #104017741
        '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer19UL18MiniAOD-106X_upgrade2018_realistic_v11_L1v1-v2/MINIAODSIM', #204151865
]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2018_' + dataset.split("/")[1]
    if "ext" in dataset:
        config.General.requestName = config.General.requestName + "_" + dataset.split("/")[2].split("_")[-1]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    #crabCommand('submit', '--dryrun', config=config)
    crabCommand('submit', config=config)
