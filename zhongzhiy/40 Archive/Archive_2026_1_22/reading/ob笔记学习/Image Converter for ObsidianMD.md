# Image Converter for ObsidianMD

Making image management inside Obsidian slightly more convenient.

[https://github.com/xRyul/obsidian-image-converter/assets/47340038/63a0646b-29ec-4055-abfc-55d31e07b2f7](https://github.com/xRyul/obsidian-image-converter/assets/47340038/63a0646b-29ec-4055-abfc-55d31e07b2f7)

## Features

Supported image formats: WEBP, JPG, PNG, HEIC, TIF

- 🖼️ **Convert**: Automatically convert dropped/pasted images into WEBP, JPG or PNG
    
- 🗜️ **Compress**: Reduce file size by specifying Quality value between 1-100
    
- 📏 **Resize** images (destructive and non-destructive)
    
    - Automatically read image dimensions and apply it to the image link e.g.: apply image width to `|width` or specify any custom size.
    - Resize by dragging edge of the image, or with Scrollwheel (e.g., **CMD+Scrollwheel**)  
          
        ![](https://github.com/xRyul/obsidian-image-converter/assets/47340038/5724c6e9-19d4-4eaf-a559-1168f6557a14)  
        
    - Resize **original** image (width, height, longest edge, shortest edge, fit, fill)
- Align (left, right center) and wrap text around images without any custom syntax in your links:  
      
    ![](https://github.com/user-attachments/assets/2224d5d3-7563-4e53-a412-cfbb975e01f5)  
    
- **Image annotation** and **markup tool**. Draw, write, scribble, annotate, markup on top of images right inside Obsidian.  
      
    ![](https://github.com/user-attachments/assets/71b8d71d-2608-441a-91cd-b7003b84d23a)![](https://github.com/user-attachments/assets/a5f74860-a473-4163-b616-f2a11a6cbc4f)  
      
    ![](https://github.com/user-attachments/assets/828c1128-719a-45ef-a5fd-cad2c7222e71)![](https://github.com/user-attachments/assets/7b1500a9-297b-4320-ba5a-9f446c6b3a4c)  
      
    ![](https://github.com/user-attachments/assets/24ab0e1a-0095-4936-84f5-61eaabd391f8)![](https://github.com/user-attachments/assets/ea312b9d-dbcf-4963-85ba-c9824c9a2153)  
    
- ✂️ **Crop, rotate, and flip images**  
      
    ![](https://github.com/user-attachments/assets/a4ead276-ac4e-4523-8567-fa064bdf7119)<![](https://github.com/user-attachments/assets/6ff7c138-90fe-456d-b968-c5fb45d27bbf)  
    
- 📁 **Custom File Management and Renaming**:
    
    - **Rename**: Use variables (e.g., `{noteName}`, `{fileName}`) to auto-rename images [List of Supported Variables](app://obsidian.md/Examples/Variables%20Reference%20Guide.md)
    - **Output**: Organize images into custom output folders with variables.[List of Supported Variables](app://obsidian.md/Examples/Variables%20Reference%20Guide.md)
- 🌍 **Pure JavaScript implementation** that works completely **offline**. No external APIs or binary dependencies (such as ImageMagick, Cloudinary, FFmpeg, sharp, etc.) required - keeping it lightweight, portable and secure.
    

## Other

- 🔄 **Batch Processing**: Convert, compress, and resize all images in a note or across the entire vault.
- 🔗 **Compatibility with other markdown editors:** Ability to have **Markdown links for images**, and **Wiki links** for all other links.
- 🖱️**Custom right click context menus:**
    - Copy to clipboard  
          
        ![](https://github.com/xRyul/obsidian-image-converter/assets/47340038/2034a444-cd49-4ce0-af98-745694ba4986)  
        
    - Copy as Base64 encoded image
    - **Resize** original image you have just clicked upon  
          
        ![](https://github.com/xRyul/obsidian-image-converter/assets/47340038/3367b41c-63fa-4a1c-a616-8561e467eef7)  
        - **Delete image from vault** - removes image and its link from the vault

## 📚 Documentation

- Settings overview
- Basic usage examples
- [Annotation tool](app://obsidian.md/Examples/Annotation%20tool.md)
- Crop tool
- [List of supported variables and use-case examples](app://obsidian.md/Examples/Variables%20Reference%20Guide.md)
- [How to compress images without quality loss - empirical analysis of image format vs image quality vs file size](app://obsidian.md/Examples/How%20to%20compress%20images%20without%20quality%20loss%20-%20empirical%20analysis%20of%20image%20format%20vs%20image%20quality%20vs%20file%20size.md)

## How to install

1. Downlaod `main.js`, `styles.css`, `manifest.json` files from the latest release page.
2. Creane new folder inside `VaultFolder/.obsidian/plugins/` named `obsidian-image-converter` . If plugins folder doesn't exist, then create it manually.
3. Move downloaded files into `/obsidian-image-converter` folder.
4. Enable the plugin in ObsidianMD.

## 🐛 Issues & Support

Found a bug or need help? [Open an issue](https://github.com/xRyul/obsidian-image-converter/issues)

If you find this plugin useful, your support keeps this project alive and growing:

[![Ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/xryul)

## 📜 License

MIT License - see [LICENSE](app://obsidian.md/LICENSE)

## 🙏 Credits

- Original inspiration from [musug's plugin](https://github.com/musug/obsidian-paste-png-to-jpeg)
- [FabricJS](https://fabricjs.com/) for annotation capabilities