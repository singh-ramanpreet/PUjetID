from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-data-cfg_UL2018.py'

config.JobType.outputFiles = ['data_flatTree.root']
#config.JobType.maxMemoryMB = 6400
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL18_RunA_V5_DATA.db',
                             'Summer19UL18_RunB_V5_DATA.db',
                             'Summer19UL18_RunC_V5_DATA.db',
                             'Summer19UL18_RunD_V5_DATA.db']

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/user/singhr/jme_ntuplesUL/'
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = ['/DoubleMuon/Run2018A-12Nov2019_UL2018-v2/MINIAOD',
                 '/DoubleMuon/Run2018B-12Nov2019_UL2018-v2/MINIAOD',
                 '/DoubleMuon/Run2018C-12Nov2019_UL2018-v2/MINIAOD',
                 '/DoubleMuon/Run2018D-12Nov2019_UL2018-v3/MINIAOD']

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    dataEra = dataset.split("/")[2].split("-")[0].replace("2018", "")
    config.JobType.scriptArgs = ["dataEra=%s" % dataEra]
    print(config.JobType.scriptArgs)
    config.General.requestName = '2018_' + dataset.split("/")[1] + "_" + dataset.split("/")[2].split("-")[0]
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    print(config)
    crabCommand('submit', config=config)
