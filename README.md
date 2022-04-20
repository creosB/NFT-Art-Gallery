<h1 class="code-line" data-line-start=0 data-line-end=1 ><a id="nft_art_gallery"></a>NFT Art Gallery</h1>
<h2 class="code-line" data-line-start=2 data-line-end=4 ><a id="NSolidhttpsplaylhgoogleusercontentcom4ChxU_bzuJe8ix7IC7fYOq5xH3rtDjDMFogy4NsF6l8jNH9Q_G7zQUWoZtWvkliyww2247h1264rwhttpwwwartistscompanydigital_2"></a><a href="http://www.artistscompany.tech"><img src="https://raw.githubusercontent.com/creosB/presentation/main/background.png" alt="N|Solid"></a></h2>
<h2 class="code-line" data-line-start=2 data-line-end=3 ><a id="1987_yapm_Contrann_Unreal_Engine_uyarlamas_olan_ve_8_blmden_oluan_bir_oyun_2"></a>Fiziksel sergi ortamını dijitale taşısaydık nasıl olurdu diye düşünerek Unreal Engine'de Metahuman, Binance ve OpenSea kullanarak bir sanat galerisi oluşturdum. Arkadaşlarınızı davet edebileceğiniz veya çok oyunculu bir şekilde başka insanlarla tanışabileceğiniz bir alan yarattığımı düşündüğüm için sizlerle paylaşmak istedim. 
<br>
Tüm bunlara ek olarak, beyaz listeye katılanların NFT yayınlarken ön gösterim yapabilecekleri ve satın alabilecekleri bir alan oluşturdum.</h2>
<h2 class="code-line" data-line-start=3 data-line-end=4 ><a id="It_is_an_Unreal_Engine_adaptation_of_1987s_Contra_and_consists_of_8_episodes_3"></a>I created an NFT Art Gallery using Metahuman, Binance, and OpenSea in Unreal Engine, thinking about what it would be like if we moved the physical exhibition environment to digital. I wanted to share it with you because I thought have created a space where you can invite your friends or meet other people in a multiplayer way.
<br>
In addition to all these, an area has been created where the whitelist participants can preview and buy while publishing NFT.</h2>
<a href="https://www.buymeacoffee.com/creos" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 41px !important;width: 174px !important;box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;-webkit-box-shadow: 0px 3px 2px 0px rgba(190, 190, 190, 0.5) !important;" ></a>
<h1 class="code-line" data-line-start=5 data-line-end=6 ><a id="zelikleri__Properties_5"></a>Özelikleri / Properties</h1>
<ul>
<li class="has-line-data" data-line-start="6" data-line-end="7">NFT bir sanat galerisi olduğu için en çok kullanılan platform olan OpenSea'yı seçtim. Bunun dışında galeride ödeme almak istiyorsanız, kişinin sadece telefonla tarayıp alabilmesi için güvenilir bir ödeme yöntemi de sağlayan Binance QR kullandım. Galerideki her şeyin kolayca değişebilmesi için kullanıcı adınızı girmeniz yeterlidir.
<br>
Since NFT is an art gallery, I chose the most used platform, namely OpenSea. Apart from that, if you want to get paid in the gallery, I used Binance QR, which also provides a reliable payment method, so that the person can only scan and receive it by phone. For everything in the gallery to change easily, you only need to enter your username.
</li>
<li class="has-line-data" data-line-start="7" data-line-end="9">EOS (epic online services) ve dedicated server kullanarak cross-platform multiplayer sistem oluşturdum. Bunun sayesinde hem Steam hem Epic Games'de olan arkadaşlarınızla birlikte oynayabilirsiniz.
<br>
I created a cross-platform multiplayer system using EOS (epic online services) and a dedicated server. Thanks to this, you can play with your friends who are on both Steam and Epic Games.
</li>
<li class="has-line-data" data-line-start="9" data-line-end="11">Kaynak kodları düzenlenmemiştir. Bundan dolayı eğer geliştirmek isteyen olursa fork isteğinde bulunması yeterlidir.
<br>
Source codes are not edited. Therefore, if anyone wants to improve, it is sufficient to request a fork.</li>
<li class="has-line-data" data-line-start="11" data-line-end="13">C++ ile geliştirilmiştir.<br>
Developed with C++.</li>
<li class="has-line-data" data-line-start="13" data-line-end="14">Oyunun oynanabilir haline alt taraftan ulaşabilirsiniz. (You can reach the playable version of the game from the bottom.)</li>
<li class="has-line-data" data-line-start="14" data-line-end="16">Alt taraftan video olarak oynanışa ve tanıtımına ulaşabilirsiniz. (You can access the gameplay and promotion as a video below.)</li>
</ul>
<hr>
<a href="https://youtu.be/GVvX_9bMIPk" title="Music Caster Video Demo">
  <p align="center">
    <img width="75%" src="https://img.youtube.com/vi/GVvX_9bMIPk/maxresdefault.jpg" alt="NFT Art Gallery Tour on Unreal Engine"/>
  </p>
</a>
<h1 class="code-line" data-line-start=24 data-line-end=25 ><a id="Bilmeniz_gerekenler__What_you_need_to_know_24"></a>Bilmeniz gerekenler / What you need to know</h1>
<ul>
<li class="has-line-data" data-line-start="25" data-line-end="27">
<ul>
<li class="has-line-data" data-line-start="25" data-line-end="27">Oyunu derlemek ve düzenlemek için **\YourEngine\Engine\Plugins\Online\OnlineSubsystemEOS** klasörünü kopyalayıp projemizin olduğu klasöre gelip plugin klasörü oluşturduktan sonra içine atıyoruz.<br>
To compile and edit the game, we copy the **\YourEngine\Engine\Plugins\Online\OnlineSubsystemEOS** folder, come to the folder where our project is located, create the plugin folder and put it in.</li>
<li class="has-line-data" data-line-start="25" data-line-end="27"><p class="has-line-data" data-line-start="0" data-line-end="1"><a href="https://github.com/creosB/UnrealScriptsandNotes/blob/main/Unreal%20Engine%20Scripts%20and%20Notes.md#eos-kullan%C4%B1m%C4%B1">Oyunu test etmek için alt kısımda bulunan ayarları yapmayı unutmayın eğer yapmazsanız, aynı bilgisayar üzerinde test edemezsiniz</a></p>
<br>
<p class="has-line-data" data-line-start="0" data-line-end="1"><a href="https://github.com/creosB/UnrealScriptsandNotes/blob/main/Unreal%20Engine%20Scripts%20and%20Notes.md#eos-kullan%C4%B1m%C4%B1">Do not forget to adjust the settings below to test the game, if you do not, you cannot test it on the same computer.</a></p></li>
</ul>
</li>
<li class="has-line-data" data-line-start="27" data-line-end="30">Boyutundan dolayı projenin tamamı yüklenememiştir. Projeye tamamen erişmek istiyorsanız buradan indirebilirsiniz.
<br>
Due to its size, the entire project could not be loaded. If you want full access to the project, you can download it here.<br>
<a href="https://drive.google.com/file/d/1a125kBrgLtBEMq_jHsNNjXtDjyEiuzXU/view?usp=sharing">Source Code</a></li>
</ul>
<h1 class="code-line" data-line-start=30 data-line-end=31 ><a id="License_30"></a>License</h1>
<hr>
<h2 class="code-line" data-line-start=32 data-line-end=33 ><a id="Herhangi_bir_yerde_paylamak_deiiklik_yapmak_iin_ncelikle_bana_ulanz_32"></a>Herhangi bir yerde paylaşmak, değişiklik yapmak için öncelikle bana ulaşınız.</h2>
<h2 class="code-line" data-line-start=33 data-line-end=34 ><a id="Please_contact_me_first_to_share_or_make_changes_anywhere_33"></a>Please contact me first to share or make changes anywhere.</h2>
<h2 class="code-line" data-line-start=34 data-line-end=35 ><a id="MIT_License_34"></a>MIT License</h2>
<hr>
