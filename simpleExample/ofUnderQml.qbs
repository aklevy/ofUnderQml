import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "../../../libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '../../..'

    ofApp {
        name: { return FileInfo.baseName(path) }

        files: [
            "src/main.cpp",
            "src/ofUnderQml.cpp",
            "src/ofUnderQml.h",
            "src/ofAppQml.cpp",
            "src/ofAppQml.h",
            
        ]

        of.addons: [

        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: ['QtKit']       // osx only, additional frameworks to link with the project

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        Depends{
            name: "Qt.quick"
        }

        Depends{
            name: "Qt.qml"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
        Group {
            name: "QML Resources"
            files: ["**/*.png", "**/*.qml", "**/*.qrc"]
            qbs.install: true
        }
    }

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
