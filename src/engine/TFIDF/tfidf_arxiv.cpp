#include "boost/algorithm/string.hpp"
#include "boost/tokenizer.hpp"
#include "tfidf.hpp"
#include <clocale>

/* we assume that we have a vector rawData whose entry is a string containing the summary of an
article for each entry we have to parse the string so that we have a vector of words
-> we want to treat a vector of vectors of words*/

std::string doc1 =
    R"(In this paper, a natural generalization of KMY model is proposed for the evaporation of charged black holes. Within the proposed model, the back reaction of Hawking radiation is considered. More specifically, we consider the equation Gμν=8π⟨Tμν⟩, in which the matter content ⟨Tμν⟩ is assumed spherically symmetric. With this equation of motion, the asymptotic behavior of the model is analyzed. Two kinds of matter contents are taken into consideration in this paper. In the first case (the thin-shell model), the infalling matter is simulated by a null-like charged sphere collapsing into its center. In the second case, we consider a continuous distribution of spherical symmetric infalling null-like charged matter. It is simulated by taking the continuous limit of many co-centric spheres collapsing into the center. We find that in the thin-shell case, an event horizon forms and the shell passes through the horizon before becoming extremal, provided that it is not initially near-extremal. In the case of continuous matter distribution, we consider explicitly an extremal center covered by neutral infalling matter and find that the event horizon also forms. The black hole itself will become near-extremal eventually, leaving possibly a non-electromagnetic energy residue less than the order of ℓ4p/e30. The details of the behavior of these models are explicitly worked out in this paper.)";
std::string doc2 =
    R"(We explore the stress-energy tensor arising from the interaction of U(1) symmetric quantum and gravitational fields. Using scalar-tensor theories of gravity, a conformal factor Ω2 is defined as the rest mass corrected by the quantum potential. The quantum potential, derived from the Klein-Gordon equation, allows for matter's intrinsic interaction with spacetime. A Lagrange multiplier λ is used as a constraint to properly couple matter with gravity. The Heisenberg uncertainty principle appears as a natural artifact of λ. Unlike the classical limit, λ in the quantum regime strongly influence the stress-energy tensor and it is therefore suggested that it is characteristic of the quantum vacuum. Additionally, the cosmological constant Λ, defined from the modified Einstein's equation, is formulated for any particle of mass m. The mysterious variation in Λ is properly evaluated from its cosmological value to that of an electron, from which we obtained a 77 order difference.)";
std::string doc3 =
    R"(We study the flight time fluctuations in an anisotropic medium inspired by a cosmic string with an effective fluctuating refractive index caused by fluctuating vacuum electric fields, which are analogous to the lightcone fluctuations due to fluctuating spacetime metric when gravity is quantized. The medium can be realized as a metamaterial that mimics a cosmic string in the sense of transformation optics. For a probe light close to the analogue string, the flight time variance is ν times that in a normal homogeneous and isotropic medium, where ν is a parameter characterizing the deficit angle of the spacetime of a cosmic string. The parameter ν, which is always greater than unity for a real cosmic string, is determined by the dielectric properties of the metamaterial for an analogue string. Therefore, the flight time fluctuations of a probe light can be manipulated by changing the electric permittivity and magnetic permeability of the analogue medium. We argue that it seems possible to fabricate a metamaterial that mimics a cosmic string with a large ν in laboratory so that a currently observable flight time variance might be achieved.)";
std::string doc4 =
    R"(The existence of a minimal measurable length as a characteristic length in the Planck scale is one of the main features of quantum gravity and has been widely explored in the context. Various different deformations of spacetime have been employed successfully for the purpose. However, polymer quantization approach is a relatively new and dynamic field towards the quantum gravity phenomenology, which emerges from the symmetric sector of the loop quantum gravity. In this article, we extend the standard ideas of polymer quantization to find a new and tighter bound on the polymer deformation parameter. Our protocol relies on an opto-mechanical experimental setup that was originally proposed in Ref.\cite{ref:Igor} to explore some interesting phenomena by embedding the minimal length into the standard canonical commutation relation. We extend this scheme to probe the \emph{polymer length} deformed canonical commutation relation of the center of mass mode of a mechanical oscillator with a mass around the Planck scale. The method utilizes the novelty of exchanging the relevant mechanical information with a high intensity optical pulse inside an optical cavity. We also demonstrate that our proposal is within the reach of the current technologies and, thus, it could uncover a decent realization of quantum gravitational phenomena thorough a simple table-top experiment.)";
std::string doc5 =
    R"(The action of the field theory is a generating functional for the equations of physics. It is introduced axiomatically by the kernel of the evolution equation. Mathematical consistency requires the lower limit of the defining proper time integral have an arbitrary positive value. This limit introduces into the dimensionless field theory the physical scale (the characteristic length), which relates geometrical orders of the action. The action is finite in all orders and nonlocal starting from the second order. Its two lowest (local) orders correspond to the cosmological constant term and the Einstein-Hilbert action of gravitation that confirm the Sakharov-DeWitt mechanism of the induced gravity. No absolute values of physical quantities are special in the field theory, therefore, the Planck scale (the Planck length etc) has no physical significance, as elucidated by the New SI of physical units. It is shown that the dimensional regularization technique is an ill-defined procedure, while regularization and renormalization are not needed for phenomenological physical theories.)";
std::vector<std::string> rawData = {doc1, doc2, doc3, doc4, doc5};

// convert a string in a vector of words
std::vector<std::string> textParse(const std::string &summary) {
    std::vector<std::string> vec;
    boost::tokenizer<> tok(summary);
    for (boost::tokenizer<>::iterator beg = tok.begin(); beg != tok.end(); ++beg) {
        std::string str = *beg;
        for (int i = 0; i < str.size(); i++) {
            str[i] = std::tolower(str[i]); // put all in lowercase
        }
        vec.push_back(str);
    }
    return vec;
}

// convert a vector of strings in a vector containing vectors of words
std::vector<std::vector<std::string>> createSetofDocs() {
    std::vector<std::vector<std::string>> data;

    for (std::string summary : rawData) {
        std::vector<std::string> wordList = textParse(summary);
        data.push_back(wordList);
    }

    return data;
}

int main() {
    std::vector<std::vector<std::string>> inputDocs = createSetofDocs();
    tfidf ins(inputDocs);
    Eigen::MatrixXd mat = ins.weightMat;
    std::cout << mat << std::endl;
}
