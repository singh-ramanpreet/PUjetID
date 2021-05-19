from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-MC-cfg_UL2016.py'

config.JobType.outputFiles = ['mc_flatTree.root']
#config.JobType.maxJobRuntimeMin = 120
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL16_V7_MC.db', 'Summer19UL16APV_V7_MC.db']

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
    '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM',
    '/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM',
    '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM',
    '/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM'
]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    ptcut="20"
    print(dataset)
    config.General.requestName = '2016_' + dataset.split("/")[1]
    if "APV" in dataset:
        config.General.requestName += '_APV'
    if "ext" in dataset:
        config.General.requestName = config.General.requestName + "_" + dataset.split("/")[2].split("_")[-1]
    print(config.General.requestName)
    config.JobType.pyCfgParams = [
        "%s" % 'isAPV=1' if "APV" in dataset else 'isAPV=0',
        "ptcut=%s" % ptcut]
    print
    config.General.requestName += "_ptcut%s" % ptcut
    config.Data.inputDataset = dataset
    print(config)
    #crabCommand('submit', '--dryrun', config=config)
    crabCommand('submit', config=config)
