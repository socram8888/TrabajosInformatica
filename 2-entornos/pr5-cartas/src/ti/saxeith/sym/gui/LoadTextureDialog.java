package ti.saxeith.sym.gui;

import java.io.File;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;

public class LoadTextureDialog extends JFileChooser {
    public LoadTextureDialog() {
        FileNameExtensionFilter extensionFilter = new FileNameExtensionFilter("Imágenes", ImageIO.getReaderFileSuffixes());
        setFileSelectionMode(JFileChooser.FILES_ONLY);
        setDialogType(JFileChooser.OPEN_DIALOG);
        setFileFilter(extensionFilter);
    }

    public File getFile() {
        if (showDialog(null, "Selecciona la textura") != JFileChooser.APPROVE_OPTION) {
            return null;
        }
        
        return getSelectedFile();
    }
}