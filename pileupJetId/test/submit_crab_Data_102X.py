from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-data-cfg_102X.py'

config.JobType.outputFiles = ['data_flatTree.root']
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 200
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/PromptReco/Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%s/jme_ntuples/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = [
    '/DoubleMuon/Run2018A-17Sep2018-v2/MINIAOD',
    '/DoubleMuon/Run2018B-17Sep2018-v1/MINIAOD',
    '/DoubleMuon/Run2018C-17Sep2018-v1/MINIAOD',
    #'/DoubleMuon/Run2018D-PromptReco-v2/MINIAOD' # change global tag for this in pset file.
]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2018_' + dataset.split("/")[1] + "_" + dataset.split("/")[2].split("-")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
