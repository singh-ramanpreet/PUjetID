from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'flat-data-cfg_UL2016.py'

config.JobType.outputFiles = ['data_flatTree.root']
config.JobType.allowUndistributedCMSSW = True

config.JobType.inputFiles = ['Summer19UL16_RunBCDEFGH_V5_DATA.db', 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt']

config.Data.inputDataset = ''

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.lumiMask = 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
config.Data.outLFNDirBase = '/store/user/singhr/jme_ntuplesUL/'
config.Data.publication = False
#config.Data.ignoreLocality = True

config.Site.storageSite = 'T3_US_FNALLPC'

#config.Site.whitelist = ['T3_US_FNALLPC']

inputDatasets = [#'/DoubleMuon/Run2016B-21Feb2020_ver1_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016B-21Feb2020_ver2_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016C-21Feb2020_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016D-21Feb2020_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016E-21Feb2020_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016F-21Feb2020_UL2016_HIPM-v1/MINIAOD',
                 '/DoubleMuon/Run2016F-21Feb2020_UL2016-v1/MINIAOD',
                 '/DoubleMuon/Run2016G-21Feb2020_UL2016-v1/MINIAOD',
                 '/DoubleMuon/Run2016H-21Feb2020_UL2016-v1/MINIAOD',]

from CRABAPI.RawCommand import crabCommand

for dataset in inputDatasets:
    print(dataset)
    dataEra = dataset.split("/")[2].split("-")[0].replace("2016", "")
    config.General.requestName = '2016_' + dataset.split("/")[1] + "_" + dataset.split("/")[2].split("-")[0]
    config.General.requestName += dataset.split("/")[2].split("-")[1].split("_")[1] if dataEra == "RunB" else ""
    config.General.requestName += '_HIPM' if dataEra == "RunF" and 'HIPM' in dataset else ""
    print(config.General.requestName)
    config.Data.inputDataset = dataset
    print(config)
    crabCommand('submit', config=config)
