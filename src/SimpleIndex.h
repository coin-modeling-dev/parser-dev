//
// Created by kingaj on 3/5/19.
//

#ifndef PARSER_DEV_SIMPLEINDEX_H
#define PARSER_DEV_SIMPLEINDEX_H

#include <vector>
#include <memory>
#include <sstream>
#include <ostream>
#include <cstdio>

typedef std::vector<unsigned int> VectorUInt;
typedef std::shared_ptr<std::vector<unsigned int> > p_VectorUnsignedInt;

class SimpleIndex {
private:
    unsigned int m_maxDim{};
    unsigned int m_maxIndex{};
    VectorUInt m_dims{};
    VectorUInt m_invIndex{};

public:

    SimpleIndex() = default;

    unsigned int getMaxDim() const {
        return m_maxDim;
    }

    explicit SimpleIndex(VectorUInt t_dims) {
        setDims(t_dims);
    }

    void clear() {
        m_maxDim = 0;
    }

    void setDims(VectorUInt t_dims) {
        m_maxDim = t_dims.size();
        m_maxIndex = 1;
        for (int i = 0; i < m_maxDim; ++i) {
            m_dims.push_back(t_dims[i]);
            m_invIndex.push_back(0);
            m_maxIndex *= t_dims[i];
        }
    }

    ~SimpleIndex() {
        clear();
    }

    friend void swap(SimpleIndex &first, SimpleIndex &second) {
        using std::swap;
        swap(first.m_maxDim, second.m_maxDim);
        swap(first.m_maxIndex, second.m_maxIndex);
        swap(first.m_dims, second.m_dims);
    }

    SimpleIndex &operator=(SimpleIndex smI) {
        swap(*this, smI);
        return *this;
    }

    int index(const VectorUInt &t_s) {
        if (t_s.size() != m_maxDim) {
            std::ostringstream e;
            std::string vector = this->displayVector(t_s);
            e << "Requested index " << vector << " has too many elements.\n";
            throw std::runtime_error(e.str());
        }
        for (unsigned int i = 0; i < m_maxDim; ++i) {
            if (t_s[i] > m_dims[i]) {
                std::ostringstream e;
                std::string vector = this->displayVector(t_s);
                e << "Requested index " << vector << " index " << i << " is larger than max " << m_dims[i]
                  << " for dimension.\n";
                throw std::runtime_error(e.str());
            }
        }

        int indx = t_s[0];
        for (unsigned int i = 1; i < m_maxDim; ++i) {
            indx *= m_dims[i];
            indx += t_s[i];
        }

        return indx;
    }

    const VectorUInt &invIndex(unsigned int n) {
        if (n >= m_maxIndex) {
            std::ostringstream e;
            e << "Index requested: " << n << " is out of range.";
            throw std::runtime_error(e.str());
        }
        for (int i = m_maxDim - 1; i > 0; --i) {
            int d1 = m_dims[i];
            m_invIndex[i] = n % m_dims[i];
            int m1 = m_invIndex[i];
            n = (n - m_invIndex[i]) / m_dims[i];
        }
        m_invIndex[0] = n;
        return m_invIndex;
//            v[4] = n % s5;
//            n = (n - v[4]) / s5;
//            v[3] = n % s4;
//            n = (n - v[3]) / s4;
//            v[2] = n % s3;
//            n = (n - v[2]) / s3;
//            v[1] = n % s2;
//            n = (n - v[1]) / s2;
//            v[0] = n;
    }


    const VectorUInt &getDimSizes() {
        return m_dims;
    }

    std::string displayVector(p_VectorUnsignedInt v) {
        return displayVector(*v);
    }

    std::string displayVector(VectorUInt v) {
        std::string out;
        out = "[";
        out += std::to_string(v[0]);
        for (int i = 1; i < v.size(); i++) {
            out += ",";
            out += std::to_string(v[i]);
        }
        out += "]";
        return out;
    }

    std::string display(unsigned int n) {
        auto v = this->invIndex(n);
        return this->displayVector(v);
    }

};

typedef std::shared_ptr<SimpleIndex> p_SMIndexed;

#endif //PARSER_DEV_SIMPLEINDEX_H
