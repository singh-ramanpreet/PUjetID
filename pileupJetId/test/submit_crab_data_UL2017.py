from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-data-cfg_UL2017.py'

config.JobType.outputFiles = ['data_flatTree.root']
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL17_RunB_V4_DATA.db',
                             'Summer19UL17_RunC_V4_DATA.db',
                             'Summer19UL17_RunD_V4_DATA.db',
                             'Summer19UL17_RunE_V4_DATA.db',
                             'Summer19UL17_RunF_V4_DATA.db']

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
config.Data.outLFNDirBase = '/store/user/singhr/jme_ntuplesUL/'
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = ['/DoubleMuon/Run2017B-09Aug2019_UL2017-v1/MINIAOD',
                 '/DoubleMuon/Run2017C-09Aug2019_UL2017-v1/MINIAOD',
                 '/DoubleMuon/Run2017D-09Aug2019_UL2017-v1/MINIAOD',
                 '/DoubleMuon/Run2017E-09Aug2019_UL2017-v1/MINIAOD',
                 '/DoubleMuon/Run2017F-09Aug2019_UL2017-v1/MINIAOD']

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    dataEra = dataset.split("/")[2].split("-")[0].replace("2017", "")
    config.JobType.scriptArgs = ["dataEra=%s" % dataEra]
    print(config.JobType.scriptArgs)
    config.General.requestName = '2017_' + dataset.split("/")[1] + "_" + dataset.split("/")[2].split("-")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    crabCommand('submit', config=config)
