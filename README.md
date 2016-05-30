# Code for performing PUjetID trainings
is documented in pileupJetId/README_Scarlet

# Code to synchronize variables on single events in AOD, MiniAOD and JMEValidator

1. Run PU jet ID on the very same RelVal event in AOD, MiniAOD and with JMEValidator. Edit the location of the output root files according to your directories. Switch to more recent RelVal samples once outdated:

cmsRun releaseValidation/fromAOD.py

cmsRun releaseValidation/fromMiniAOD.py

cmsRun runFrameworkMC.py (after editing the input file to the same as in fromMiniAOD.py)

2. Print the variables on the first couple of events

python printAOD.py

python print_MiniAOD.py

python check_JMEValidator_vars.py

Below is how the names correspond to eachother in CMSSW and JME Validator

CMSSW=JMEValidator

pt=pt

eta=pt

fullDiscriminant=PUJetId_fullDiscriminant

beta=beta

betaClassic=betaClassic

betaStar=betaStar

betaStarClassic=betaStarClassic

dR2Mean=DRweighted

dRMatch=dRMatch

dZ=dZ

frac01=fRing0

frac02=fRing1

frac03=fRing2

frac04=fRing3

jetR=jetR

jetRchg=jetRchg

majW=axisMajor

minW=axisMinor

nCharged=nCh

nNeutrals=nNeutrals

nParticles=nTot

ptD=ptD

pull=pull
