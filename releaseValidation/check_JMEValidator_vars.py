from ROOT import *

f=TFile.Open("output_mc.root","read")
t=f.Get("AK4PFCHS/t")
var=["PUJetId_fullDiscriminant",
"beta","betaClassic","betaStar","betaStarClassic",
"DRweighted",
"dRMatch",
"dZ",
"fRing0","fRing1","fRing2","fRing3","jetR","jetRchg","axisMajor","axisMinor","nCh","nNeutrals","nTot","ptD","pull",
]
for e in t:
  if e.p4[0].Pt() < 20 or abs(e.p4[0].Eta())>1: continue
  string="pt "+str(e.p4[0].Pt())+", eta "+str(e.p4[0].Eta())+", jec "+str(e.jec_factors[0]["Uncorrected"])
  for v in var:
    string+=", "+v+" "+str(getattr(e,v)[0])
  print string
