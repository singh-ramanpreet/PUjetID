from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-data-cfg_94X.py'

config.JobType.outputFiles = ['data_flatTree.root']
#config.JobType.maxMemoryMB = 6400

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
config.Data.outLFNDirBase = '/store/user/%s/jets_2017/' % (getUsernameFromSiteDB())
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = ['/DoubleMuon/Run2017B-31Mar2018-v1/MINIAOD',
                 '/DoubleMuon/Run2017C-31Mar2018-v1/MINIAOD',
                 '/DoubleMuon/Run2017D-31Mar2018-v1/MINIAOD',
                 '/DoubleMuon/Run2017E-31Mar2018-v1/MINIAOD',
                 '/DoubleMuon/Run2017F-31Mar2018-v1/MINIAOD']

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    config.General.requestName = '2017_' + dataset.split("/")[1] + "_" + dataset.split("/")[2].split("-")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
