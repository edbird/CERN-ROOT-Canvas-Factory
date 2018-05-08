#ifndef CANVASFACTORY_HPP
#define CANVASFACTORY_HPP

#include <vector>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1.h>
#include <TLegend.h>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// EXAMPLE CODE
// OLD METHOD OF DOING EVERYTHING
////////////////////////////////////////////////////////////////////////////////

// load from NEMO-3 data (MC), the reconstructed electron energy (2 in same histogram)
//TH1D *h_el_energy_original = new TH1D("h_el_energy_original", "", num_bins, 0.0, 4.0);
//h_el_energy_original->SetStats(0);
//h_el_energy_original->SetLineColor(2);
//h_el_energy_original->SetMarkerColor(2);
// same as above but re-weighted
//TH1D *h_el_energy_reweight = new TH1D("h_el_energy_reweight", "", num_bins, 0.0, 4.0);
//h_el_energy_reweight->SetStats(0);
//h_el_energy_reweight->SetLineColor(4);
//h_el_energy_reweight->SetMarkerColor(4);

// print single electron distribution
//TCanvas *c_el_energy_both = new TCanvas("e_el_energy_both", "e_el_energy_both", 800, 600);
//c_el_energy_both->SetLogy(log_mode);
//h_el_energy_original->SetMaximum(220.0e3); // MC data
//h_el_energy_original->SetMaximum(1000.0e3); // MC data log mode
//h_el_energy_original->GetXaxis()->SetTitle("Energy [MeV]");
//h_el_energy_original->GetYaxis()->SetTitle("Events");
//h_el_energy_reweight->SetMaximum(1000.0e3);
//h_el_energy_reweight->GetXaxis()->SetTitle("Energy [MeV]");
//h_el_energy_reweight->GetYaxis()->SetTitle("Events");
//h_el_energy_original->Draw("E");
//h_el_energy_reweight->Draw("Esame");
//c_el_energy_both->SaveAs("c_el_energy_both.C");
//c_el_energy_both->SaveAs("c_el_energy_both.png");
//c_el_energy_both->SaveAs("c_el_energy_both.pdf");
//delete c_el_energy_both;


////////////////////////////////////////////////////////////////////////////////
// EXAMPLE CODE
// NEW METHOD OF DOING EVERYTHING
////////////////////////////////////////////////////////////////////////////////

//CanvasFactorySettings s("x_axis", "y_axis", 200.0e3, 0.0, false);
//s.SetAxisFont(4);
//s.SetAxisFontSize(0.03);
//s.SetDrawOption("E");
//CanvasFactory f(s);
//TH1D *h_el_energy_original = new TH1D("h_el_energy_original", "", num_bins, 0.0, 4.0);
//TH1D *h_el_energy_reweight = new TH1D("h_el_energy_reweight", "", num_bins, 0.0, 4.0);
//f.Canvas("el_energy", "el_energy_nolog_dir", h_el_energy_original, h_el_energy_reweight);

class CanvasFactory;

class CanvasFactorySettings
{

    friend class CanvasFactory;

    // axis title text
    std::string _x_axis_title_text_;
    std::string _y_axis_title_text_;

    // axis title font and font size
    Int_t _axis_title_font_;
    Double_t _axis_title_font_size_;

    // axis label font size
    Int_t _axis_label_font_;
    Double_t _axis_label_font_size_;
    
    // default axis label font can be changed here
    const Int_t _DEFAULT_AXIS_TITLE_FONT_;//{42};
    // default axis label font size can be changed here
    const Double_t _DEFAULT_AXIS_TITLE_FONT_SIZE_;//{0.035};
    // default axis number font can be changed here
    const Int_t _DEFAULT_AXIS_LABEL_FONT_;//{42};
    // default axis number font size can be changed here
    const Double_t _DEFAULT_AXIS_LABEL_FONT_SIZE_;//{0.035};

    // canvas log mode switch
    bool _log_mode_;

    // histogram draw option
    // draw options - default for all histograms,
    // TODO: over-ride on per-histogram basis
    // option "same" automatically included for histograms after first is drawn
    std::string _draw_opt_;

    // min / max limits for histograms
    Double_t _maximum_;
    Double_t _minimum_;

    // canvas png image width / height
    Int_t _canvas_width_;
    Int_t _canvas_height_;
    const Int_t _DEFAULT_CANVAS_WIDTH_;//{804}; // 800 + (800 - 796)
    const Int_t _DEFAULT_CANVAS_HEIGHT_;//{628}; // 600 + (600 - 572)

    // legend size and position
    Double_t _legend_x_;//{0.7}; // TODO
    Double_t _legend_y_;//{0.7};
    Double_t _legend_w_;//{0.2};
    Double_t _legend_h_;//{0.2};

    Double_t _DEFAULT_LEGEND_X_;
    Double_t _DEFAULT_LEGEND_Y_;
    Double_t _DEFAULT_LEGEND_W_;
    Double_t _DEFAULT_LEGEND_H_;

    // legend font and font size
    Int_t _legend_font_;
    const Int_t _DEFAULT_LEGEND_FONT_;
    Double_t _legend_font_size_;
    const Double_t _DEFAULT_LEGEND_FONT_SIZE_;

    // legend enable (force legend when only 1 data drawn)
    bool _legend_enable_;
    

    ////////////////////////////////////////////////////////////////////////////
    // PRIVATE FUNCTIONS
    ////////////////////////////////////////////////////////////////////////////

    Int_t get_histogram_color(const std::size_t index, const std::size_t count)
    {
        if(count == 1)
        {
            return 4; // blue
        }
        else if(count == 2)
        {   
            if(index == 0) return 4; // blue
            else return 2; // red
        }
        /*
        else if(count == 3)
        {
            if(index == 0) return 2; // red
            else if(index == 1) return 3; // green
            else return 4; // blue
        }
        */
        else if(count <= 4)
        {
            if(index == 0) return 2; // red
            else if(index == 1) return 3; // green
            else if(index == 2) return 4; // blue
            else return 1; // black
        } 
        else if(count <= 6)
        {
            if(index == 0) return 2; // red
            else if(index == 1) return 3; // green
            else if(index == 2) return 4; // blue
            else if(index == 3) return 6; // magenta
            else if(index == 4) return 7; // cyan
            else return 1; // black
        }
        else if(count <= 10)
        {
            if(index == 0) return 1; // black
            else if(index == 1) return kOrange + 4; // brown
            else if(index == 2) return 2; // red
            else if(index == 3) return kOrange + 7; // orange
            else if(index == 4) return kOrange - 2; // yellow
            else if(index == 5) return 3; // green
            else if(index == 6) return 7; // cyan
            else if(index == 7) return 4; // blue
            else if(index == 8) return kViolet; // purple
            else if(index == 9) return kBlack + 2; // grey
        }
        else
        {
            if(index <= 15)
            {
                return (kBlue - 10) + index;
            }
            else
            {
                return (kViolet - 9) + index;
            }
        }


    }



    public:

    CanvasFactorySettings(const std::string& x_axis_title_text, const std::string& y_axis_title_text,
                          const Double_t minimum = 1.0, const Double_t maximum = 0.0,
                          const bool log_mode = false)
        : _DEFAULT_AXIS_TITLE_FONT_{42}
        , _DEFAULT_AXIS_TITLE_FONT_SIZE_{0.035}
        , _DEFAULT_AXIS_LABEL_FONT_{42}
        , _DEFAULT_AXIS_LABEL_FONT_SIZE_{0.035}
        , _DEFAULT_CANVAS_WIDTH_{804}
        , _DEFAULT_CANVAS_HEIGHT_{628}
        , _DEFAULT_LEGEND_X_{0.7}
        , _DEFAULT_LEGEND_Y_{0.7}
        , _DEFAULT_LEGEND_W_{0.2}
        , _DEFAULT_LEGEND_H_{0.2}
        , _DEFAULT_LEGEND_FONT_{42}
        , _DEFAULT_LEGEND_FONT_SIZE_{0.035}
        , _x_axis_title_text_{x_axis_title_text}
        , _y_axis_title_text_{y_axis_title_text}
        //, _axis_title_font_{_DEFAULT_AXIS_TITLE_FONT_}
        //, _axis_title_font_size_{_DEFAULT_AXIS_TITLE_FONT_SIZE_}
        //, _axis_label_font_size_{_DEFAULT_AXIS_LABEL_FONT_SIZE_}
        , _log_mode_{log_mode}
        //, _draw_opt_{""}
        , _maximum_{maximum}
        , _minimum_{minimum}
        //, _canvas_width_{_DEFAULT_CANVAS_WIDTH_}
        //, _canvas_height_{_DEFAULT_CANVAS_HEIGHT_}
        , _legend_enable_{false}
    {
        _axis_title_font_ = _DEFAULT_AXIS_TITLE_FONT_;
        _axis_title_font_size_ = _DEFAULT_AXIS_TITLE_FONT_SIZE_;
        _axis_label_font_ = _DEFAULT_AXIS_LABEL_FONT_;
        _axis_label_font_size_ = _DEFAULT_AXIS_LABEL_FONT_SIZE_;
        _canvas_width_ = _DEFAULT_CANVAS_WIDTH_;
        _canvas_height_ = _DEFAULT_CANVAS_HEIGHT_;
        _legend_x_ = _DEFAULT_LEGEND_X_;
        _legend_y_ = _DEFAULT_LEGEND_Y_;
        _legend_w_ = _DEFAULT_LEGEND_W_;
        _legend_h_ = _DEFAULT_LEGEND_H_;
        _legend_font_ = _DEFAULT_LEGEND_FONT_;
        _legend_font_size_ = _DEFAULT_LEGEND_FONT_SIZE_;
    }

    void SetAxisTitleFont(const Int_t font)
    {
        _axis_title_font_ = font;
    }

    void SetAxisTitleFontSize(const Double_t size)
    {
        _axis_title_font_size_ = size;
    }

    void SetAxisLabelFont(const Int_t font)
    {
        _axis_label_font_ = font;
    }

    void SetAxisLabelFontSize(const Double_t size)
    {
        _axis_label_font_size_ = size;
    }

    void SetXaxisTitleText(const std::string& text)
    {
        _x_axis_title_text_ = text;
    }

    void SetYaxisTitleText(const std::string& text)
    {
        _y_axis_title_text_ = text;
    }

    void SetLogMode(const bool log_mode)
    {
        _log_mode_ = log_mode;
    }

    void SetLimits(const Double_t minimum, const Double_t maximum)
    {
        _minimum_ = minimum;
        _maximum_ = maximum;
    }

    void SetDrawOption(const std::string& draw_opt)
    {
        _draw_opt_ = draw_opt;
    }

    void SetCanvasSize(const Int_t width, const Int_t height)
    {
        _canvas_width_ = width;
        _canvas_height_ = height;
    }

    void SetLegendSize(const Double_t width, const Double_t height)
    {
        _legend_w_ = width;
        _legend_h_ = height;
    }

    void SetLegendPosition(const Double_t pos_x, const Double_t pos_y)
    {
        _legend_x_ = pos_x;
        _legend_y_ = pos_y;
    }

    void SetLegend(const Double_t pos_x, const Double_t pos_y, const Double_t width, const Double_t height)
    {
        SetLegendPosition(pos_x, pos_y);
        SetLegendSize(width, height);
    }

    void SetLegendEnable(const bool enabled = true)
    {
        _legend_enable_ = enabled;
    }


};


class CanvasFactory
{

    CanvasFactorySettings _settings_;

    public:

    // used to set all CavnasFactory with same settings
    CanvasFactory(const CanvasFactorySettings &settings)
        : _settings_{settings}
    {
    }

    // used to set settings for each CanvasFactory individually
    CanvasFactory(const std::string& x_axis_title_text, const std::string& y_axis_title_text,
                  const Double_t maximum = 1.0, const Double_t minimum = 0.0,
                  const bool log_mode = false)
        : _settings_(x_axis_title_text, y_axis_title_text, maximum, minimum, log_mode)
    {
    }

    // used to return the settings so that they can be modified
    CanvasFactorySettings& Settings()
    {
        return _settings_;
    }

    // entry point function, no directory
    template<typename... Targs>
    void Canvas(const std::string& filename,
                TH1* histo, const std::string& legend_text,
                //TH1* histo, const char* legend_text,
                Targs... Fargs)
    {
        Canvas(filename, "", histo, legend_text, Fargs...);
    }

    // entry point function
    template<typename... Targs>
    void Canvas(const std::string& filename, const std::string& directory,
                TH1* histo, const std::string& legend_text,
                //TH1* histo, const char* legend_text,
                Targs... Fargs)
    {
        std::vector<TH1*> histo_ptr;
        histo_ptr.push_back(histo);
        // TODO
        //std::vector<std::pair<TH1*, const std::string>> histo_ptr;
        //histo_ptr.push_back({histo, histo_legend_text});

        std::vector<std::string> histo_legend_text;
        histo_legend_text.push_back(legend_text);
        //histo_legend_text.push_back(std::string(legend_text));

        // call recursive function
        Canvas(histo_ptr, histo_legend_text, Fargs...);

        // log mode string (maybe path?)
        std::string log_mode_string;
        if(_settings_._log_mode_)
        {
            log_mode_string = std::string("_log");
        }

        // output file
        std::string full_filename{directory + std::string("/") + filename + log_mode_string + std::string(".root")};
        TFile *f_local{new TFile(full_filename.c_str(), "recreate")};

        // output canvas
        std::string full_canvasname_noext{directory + std::string("/") + filename + log_mode_string};
        std::cout << "Canvas size: " << _settings_._canvas_width_ << ", " << _settings_._canvas_height_ << std::endl;
        //std::cout << "Canvas Width and Height: " << _DEFAULT_CANVAS_WIDTH_ << " " << _DEFAULT_CANVAS_HEIGHT_ << std::endl;
        //std::cout << "Canvas Width and Height: " << _canvas_width_ << " " << _canvas_height_ << std::endl;
        TCanvas *c_local{new TCanvas(full_canvasname_noext.c_str(), "", _settings_._canvas_width_, _settings_._canvas_height_)};
        c_local->SetLogy(_settings_._log_mode_);

        // legend
        TLegend *legend = new TLegend(_settings_._legend_x_,
                                      _settings_._legend_y_,
                                      _settings_._legend_x_ + _settings_._legend_w_,
                                      _settings_._legend_y_ + _settings_._legend_h_);
        legend->SetTextFont(_settings_._legend_font_);
        legend->SetTextSize(_settings_._legend_font_size_);
        std::string legend_opt("l"); // TODO

        // when recursive functions returns, vector contains all histogram pointers
        typedef std::vector<TH1*>::iterator Iterator_t;
        Iterator_t it{histo_ptr.begin()};
        for(; it != histo_ptr.end(); ++ it)
        {
            // index of current histogram
            long long index{std::distance(histo_ptr.begin(), it)};

            // set histogram options
            
            // statsbox
            (*it)->SetStats(0);

            // colors
            Int_t color{_settings_.get_histogram_color(index, histo_ptr.size())};
            (*it)->SetLineColor(color);
            (*it)->SetMarkerColor(color);
            
            // min / max
            (*it)->SetMaximum(_settings_._maximum_);
            (*it)->SetMinimum(_settings_._minimum_);

            // axis label font
            (*it)->GetXaxis()->SetLabelFont(_settings_._axis_label_font_);
            (*it)->GetYaxis()->SetLabelFont(_settings_._axis_label_font_);
            // axis label size
            (*it)->GetXaxis()->SetLabelSize(_settings_._axis_label_font_size_); // TODO check these are correct
            (*it)->GetYaxis()->SetLabelSize(_settings_._axis_label_font_size_);

            // axis title font
            (*it)->GetXaxis()->SetTitleFont(_settings_._axis_title_font_);
            (*it)->GetYaxis()->SetTitleFont(_settings_._axis_title_font_);
            // axis title font size
            (*it)->GetXaxis()->SetTitleSize(_settings_._axis_title_font_size_);
            (*it)->GetYaxis()->SetTitleSize(_settings_._axis_title_font_size_);

            // axis title text
            (*it)->GetXaxis()->SetTitle(_settings_._x_axis_title_text_.c_str());
            (*it)->GetYaxis()->SetTitle(_settings_._y_axis_title_text_.c_str());

            // draw to canvas
            std::string draw_opt{_settings_._draw_opt_};
            if(index > 0) draw_opt += std::string("same");
            (*it)->Draw(draw_opt.c_str());

            // write histogram to file
            (*it)->Write();

            // legend
            std::string legend_text{histo_legend_text.at(index)};
            legend->AddEntry(*it, legend_text.c_str(), legend_opt.c_str());

        }

        // draw legend if more than 2 sets of data
        if(_settings_._legend_enable_ || std::distance(histo_ptr.begin(), histo_ptr.end()) > 1)
        {
            std::cout << "The number of histograms is: " << std::distance(histo_ptr.begin(), histo_ptr.end()) << std::endl;
            legend->Draw();
        }

        // save canvas as png, eps, pdf and C output
        std::vector<std::string> ext{".png", ".eps", ".pdf", ".C"};
        //for(std::vector<const std::string>::const_iterator ext_it{ext.cbegin()}; ext_it != ext.cend(); ++ ext_it)
        std::vector<std::string>::const_iterator ext_it{ext.cbegin()};
        for(; ext_it != ext.cend(); ++ ext_it)
        {
            std::string full_canvasname_ext{full_canvasname_noext + (*ext_it)};
            c_local->SaveAs(full_canvasname_ext.c_str());
        }

        // write canvas to file
        c_local->Write();

        // close file
        f_local->Close();
    }

    // recursive function
    template<typename... Targs>
    void Canvas(std::vector<TH1*> &histo_ptr, std::vector<std::string> &histo_legend_text,
                TH1* histo, const std::string& legend_text,
                //TH1* histo, const char* legend_text,
                Targs... Fargs)
    {
        // add histogram pointer and legend text to storage
        histo_ptr.push_back(histo);
        histo_legend_text.push_back(legend_text);

        Canvas(histo_ptr, histo_legend_text, Fargs...);
    }

    // terminating function
    // TODO: is this needed
    template<typename... Targs>
    void Canvas(std::vector<TH1*> &histo_ptr, std::vector<std::string> &histo_legend_text,
                TH1* histo, const std::string& legend_text)
                //TH1* histo, const char* legend_text)
    {
        // add histogram pointer and legend text to storage
        histo_ptr.push_back(histo);
        histo_legend_text.push_back(legend_text);
    }


};


#endif // CANVASFACTORY_HPP

