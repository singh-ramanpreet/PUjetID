void DrawROC()
{
  gROOT->ForceStyle();
  TFile *inf = TFile::Open("Histo_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_0.root");

  const int NTYPE = 3;
  const int NETA  = 4;
  const int NPT   = 3;
  float ETABND[NETA+1] = {0,2.5,2.75,3,5};
  float PTBND[NPT+1]   = {20,30,50,100};  
  float LOOSE[NETA]    = {0.99,0.95,0.95,0.95};
  float MEDIUM[NETA]   = {0.90,0.90,0.90,0.90};
  float TIGHT[NETA]    = {0.80,0.80,0.80,0.80};
  int COLOR[NTYPE] = {kRed,kBlue,kGreen+2};
 
  TH1F *h[NETA][NPT][NTYPE];
  TH1F *hF[NETA][NPT][NTYPE]; 

  TH2F *hEffLoose[NTYPE],*hEffMedium[NTYPE],*hEffTight[NTYPE];

  float vLoose[NPT][NETA],vMedium[NPT][NETA],vTight[NPT][NETA];

  gStyle->SetPaintTextFormat("1.2g");
  gStyle->SetPalette(12,0);

  for(int k=0;k<NTYPE;k++) {
    hEffLoose[k] = new TH2F(TString::Format("hEffLoose_Type%d",k),TString::Format("hEffLoose_Type%d",k),NPT,PTBND,NETA,ETABND);
    hEffMedium[k] = new TH2F(TString::Format("hEffMedium_Type%d",k),TString::Format("hEffMedium_Type%d",k),NPT,PTBND,NETA,ETABND);
    hEffTight[k] = new TH2F(TString::Format("hEffTight_Type%d",k),TString::Format("hEffTight_Type%d",k),NPT,PTBND,NETA,ETABND);
    hEffLoose[k]->SetMarkerSize(2.5);
    hEffMedium[k]->SetMarkerSize(2.5);
    hEffTight[k]->SetMarkerSize(2.5);
    for(int ieta=0;ieta<NETA;ieta++) {
      for(int ipt=0;ipt<NPT;ipt++) { 
        h[ieta][ipt][k] = (TH1F*)inf->Get("jetmet/"+TString::Format("h_pumva_Type%d_Pt%d_Eta%d",k,ipt,ieta)); 
        h[ieta][ipt][k]->Scale(1./h[ieta][ipt][k]->Integral()); 
        hF[ieta][ipt][k] = (TH1F*)h[ieta][ipt][k]->Clone(TString(h[ieta][ipt][k]->GetName())+"_Cumulative");
        hF[ieta][ipt][k]->Reset();
        hF[ieta][ipt][k]->SetLineColor(COLOR[k]); 
        hF[ieta][ipt][k]->SetLineWidth(2); 
        for(int i=0;i<h[ieta][ipt][k]->GetNbinsX();i++) {
          float e = 1-h[ieta][ipt][k]->Integral(0,i+1);
          hF[ieta][ipt][k]->SetBinContent(i+1,e);
        }
      }
    }
  }

  TCanvas *can = new TCanvas("Cumualtive","Cumulative",1100,900);
  can->Divide(NPT,NETA);
  int n(1);
  for(int ieta=0;ieta<NETA;ieta++) {
    for(int ipt=0;ipt<NPT;ipt++) {
      can->cd(n); 

      int binLoose = hF[ieta][ipt][0]->FindLastBinAbove(LOOSE[ieta]);
      int binMedium = hF[ieta][ipt][0]->FindLastBinAbove(MEDIUM[ieta]);
      int binTight = hF[ieta][ipt][0]->FindLastBinAbove(TIGHT[ieta]);

      float cutLoose = hF[ieta][ipt][0]->GetBinLowEdge(binLoose+1);
      float cutMedium = hF[ieta][ipt][0]->GetBinLowEdge(binMedium+1);
      float cutTight = hF[ieta][ipt][0]->GetBinLowEdge(binTight+1);

      vLoose[ipt][ieta]  = cutLoose;
      vMedium[ipt][ieta] = cutMedium;
      vTight[ipt][ieta]  = cutTight;

      for(int k=0;k<3;k++) {
        hEffLoose[k]->SetBinContent(ipt+1,ieta+1,hF[ieta][ipt][k]->GetBinContent(binLoose));
        hEffMedium[k]->SetBinContent(ipt+1,ieta+1,hF[ieta][ipt][k]->GetBinContent(binMedium));
        hEffTight[k]->SetBinContent(ipt+1,ieta+1,hF[ieta][ipt][k]->GetBinContent(binTight));
      }

      //hF[ieta][ipt][0]->GetYaxis()->SetRangeUser(0.5,1); 
      hF[ieta][ipt][0]->GetXaxis()->SetTitle("mva");
      hF[ieta][ipt][0]->GetYaxis()->SetTitle("efficiency");
      hF[ieta][ipt][0]->Draw();
      hF[ieta][ipt][1]->Draw("same");
      hF[ieta][ipt][2]->Draw("same");

      gPad->Update();

      TLine *lnLoose = new TLine(gPad->GetFrame()->GetX1(),LOOSE[ieta],gPad->GetFrame()->GetX2(),LOOSE[ieta]);
      lnLoose->SetLineColor(kBlack);
      lnLoose->SetLineWidth(1);
      lnLoose->SetLineStyle(2);
      lnLoose->Draw();
      TLine *lnMedium = new TLine(gPad->GetFrame()->GetX1(),MEDIUM[ieta],gPad->GetFrame()->GetX2(),MEDIUM[ieta]);
      lnMedium->SetLineColor(kBlack);
      lnMedium->SetLineWidth(1);
      lnMedium->SetLineStyle(2);
      lnMedium->Draw();
      TLine *lnTight = new TLine(gPad->GetFrame()->GetX1(),TIGHT[ieta],gPad->GetFrame()->GetX2(),TIGHT[ieta]);
      lnTight->SetLineColor(kBlack);
      lnTight->SetLineWidth(1);
      lnTight->SetLineStyle(2);
      lnTight->Draw();
      n++;
    }
  }

  TCanvas *can1 = new TCanvas("Efficiencies","Efficiencies",1100,900);
  can1->Divide(3,3);   
  for(int k=0;k<3;k++) {
    can1->cd(3*k+1); 
    hEffLoose[k]->SetMaximum(1.0);
    hEffLoose[k]->SetMinimum(0.0);
    hEffLoose[k]->GetXaxis()->SetTitle("p_{T} (GeV)");
    hEffLoose[k]->GetYaxis()->SetTitle("|#eta|");
    hEffLoose[k]->Draw("text col");
    can1->cd(3*k+2); 
    hEffMedium[k]->SetMaximum(1.0);
    hEffMedium[k]->SetMinimum(0.0);
    hEffMedium[k]->GetXaxis()->SetTitle("p_{T} (GeV)");
    hEffMedium[k]->GetYaxis()->SetTitle("|#eta|");
    hEffMedium[k]->Draw("text col");
    can1->cd(3*k+3);
    hEffTight[k]->SetMaximum(1.0);
    hEffTight[k]->SetMinimum(0.0);
    hEffTight[k]->GetXaxis()->SetTitle("p_{T} (GeV)");
    hEffTight[k]->GetYaxis()->SetTitle("|#eta|");
    hEffTight[k]->Draw("text col");
  }

  for(int ipt=0;ipt<NPT;ipt++) {
    cout<<"Pt"<<PTBND[ipt]<<PTBND[ipt+1]<<"_Tight = ";
    for(int ieta=0;ieta<NETA;ieta++) {
      cout<<vTight[ipt][ieta]<<" ";
    }
    cout<<endl;
    cout<<"Pt"<<PTBND[ipt]<<PTBND[ipt+1]<<"_Medium = ";
    for(int ieta=0;ieta<NETA;ieta++) {
      cout<<vMedium[ipt][ieta]<<" ";
    }
    cout<<endl;  
    cout<<"Pt"<<PTBND[ipt]<<PTBND[ipt+1]<<"_Loose = ";
    for(int ieta=0;ieta<NETA;ieta++) {
      cout<<vLoose[ipt][ieta]<<" ";
    }
    cout<<endl;
  }
}







